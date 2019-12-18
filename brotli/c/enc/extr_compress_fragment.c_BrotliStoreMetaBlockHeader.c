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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint64_t ;
typedef  scalar_t__ BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliWriteBits (int,size_t,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void BrotliStoreMetaBlockHeader(
    size_t len, BROTLI_BOOL is_uncompressed, size_t* storage_ix,
    uint8_t* storage) {
  size_t nibbles = 6;
  /* ISLAST */
  BrotliWriteBits(1, 0, storage_ix, storage);
  if (len <= (1U << 16)) {
    nibbles = 4;
  } else if (len <= (1U << 20)) {
    nibbles = 5;
  }
  BrotliWriteBits(2, nibbles - 4, storage_ix, storage);
  BrotliWriteBits(nibbles * 4, len - 1, storage_ix, storage);
  /* ISUNCOMPRESSED */
  BrotliWriteBits(1, (uint64_t)is_uncompressed, storage_ix, storage);
}