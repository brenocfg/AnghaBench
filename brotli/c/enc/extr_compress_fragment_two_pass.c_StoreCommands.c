#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int const uint16_t ;
typedef  int /*<<< orphan*/  MemoryManager ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_DCHECK (int) ; 
 scalar_t__ BROTLI_IS_OOM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BrotliBuildAndStoreHuffmanTreeFast (int /*<<< orphan*/ *,int*,size_t const,int,size_t*,int const*,size_t*,size_t*) ; 
 int /*<<< orphan*/  BrotliWriteBits (int const,int const,size_t*,size_t*) ; 
 int /*<<< orphan*/  BuildAndStoreCommandPrefixCode (int*,size_t*,int const*,size_t*,size_t*) ; 

__attribute__((used)) static void StoreCommands(MemoryManager* m,
                          const uint8_t* literals, const size_t num_literals,
                          const uint32_t* commands, const size_t num_commands,
                          size_t* storage_ix, uint8_t* storage) {
  static const uint32_t kNumExtraBits[128] = {
    0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 9, 10, 12, 14, 24,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 9, 10, 24,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8,
    9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24,
  };
  static const uint32_t kInsertOffset[24] = {
    0, 1, 2, 3, 4, 5, 6, 8, 10, 14, 18, 26, 34, 50, 66, 98, 130, 194, 322, 578,
    1090, 2114, 6210, 22594,
  };

  uint8_t lit_depths[256];
  uint16_t lit_bits[256];
  uint32_t lit_histo[256] = { 0 };
  uint8_t cmd_depths[128] = { 0 };
  uint16_t cmd_bits[128] = { 0 };
  uint32_t cmd_histo[128] = { 0 };
  size_t i;
  for (i = 0; i < num_literals; ++i) {
    ++lit_histo[literals[i]];
  }
  BrotliBuildAndStoreHuffmanTreeFast(m, lit_histo, num_literals,
                                     /* max_bits = */ 8,
                                     lit_depths, lit_bits,
                                     storage_ix, storage);
  if (BROTLI_IS_OOM(m)) return;

  for (i = 0; i < num_commands; ++i) {
    const uint32_t code = commands[i] & 0xFF;
    BROTLI_DCHECK(code < 128);
    ++cmd_histo[code];
  }
  cmd_histo[1] += 1;
  cmd_histo[2] += 1;
  cmd_histo[64] += 1;
  cmd_histo[84] += 1;
  BuildAndStoreCommandPrefixCode(cmd_histo, cmd_depths, cmd_bits,
                                 storage_ix, storage);

  for (i = 0; i < num_commands; ++i) {
    const uint32_t cmd = commands[i];
    const uint32_t code = cmd & 0xFF;
    const uint32_t extra = cmd >> 8;
    BROTLI_DCHECK(code < 128);
    BrotliWriteBits(cmd_depths[code], cmd_bits[code], storage_ix, storage);
    BrotliWriteBits(kNumExtraBits[code], extra, storage_ix, storage);
    if (code < 24) {
      const uint32_t insert = kInsertOffset[code] + extra;
      uint32_t j;
      for (j = 0; j < insert; ++j) {
        const uint8_t lit = *literals;
        BrotliWriteBits(lit_depths[lit], lit_bits[lit], storage_ix, storage);
        ++literals;
      }
    }
  }
}