#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  dist_cache ;
struct TYPE_8__ {int /*<<< orphan*/  alphabet_size_limit; } ;
struct TYPE_9__ {TYPE_1__ dist; int /*<<< orphan*/  quality; int /*<<< orphan*/  size_hint; int /*<<< orphan*/  disable_literal_context_modeling; } ;
typedef  int /*<<< orphan*/  MetaBlockSplit ;
typedef  int /*<<< orphan*/  MemoryManager ;
typedef  int /*<<< orphan*/  ContextType ;
typedef  int /*<<< orphan*/  ContextLut ;
typedef  int /*<<< orphan*/  Command ;
typedef  TYPE_2__ BrotliEncoderParams ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_CONTEXT_LUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BROTLI_DCHECK (int) ; 
 scalar_t__ BROTLI_IS_OOM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BrotliBuildMetaBlock (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/  const,size_t const,TYPE_2__*,int const,int const,int /*<<< orphan*/ *,size_t const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BrotliBuildMetaBlockGreedy (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/  const,size_t const,int const,int const,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BrotliOptimizeHistograms (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BrotliStoreMetaBlock (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/  const,size_t const,size_t const,int const,int const,int /*<<< orphan*/  const,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t const,int /*<<< orphan*/ *,size_t*,int*) ; 
 int /*<<< orphan*/  BrotliStoreMetaBlockFast (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/  const,size_t const,size_t const,int /*<<< orphan*/  const,TYPE_2__ const*,int /*<<< orphan*/ *,size_t const,size_t*,int*) ; 
 int /*<<< orphan*/  BrotliStoreMetaBlockTrivial (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/  const,size_t const,size_t const,int /*<<< orphan*/  const,TYPE_2__ const*,int /*<<< orphan*/ *,size_t const,size_t*,int*) ; 
 int /*<<< orphan*/  BrotliStoreUncompressedMetaBlock (int /*<<< orphan*/  const,int const*,int /*<<< orphan*/  const,size_t const,size_t const,size_t*,int*) ; 
 int /*<<< orphan*/  BrotliWriteBits (int,int,size_t*,int*) ; 
 int /*<<< orphan*/  DecideOverLiteralContextModeling (int const*,int /*<<< orphan*/  const,size_t const,size_t const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  DestroyMetaBlockSplit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitMetaBlockSplit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_QUALITY_FOR_STATIC_ENTROPY_CODES ; 
 int /*<<< orphan*/  MIN_QUALITY_FOR_BLOCK_SPLIT ; 
 int /*<<< orphan*/  MIN_QUALITY_FOR_HQ_BLOCK_SPLITTING ; 
 int /*<<< orphan*/  MIN_QUALITY_FOR_OPTIMIZE_HISTOGRAMS ; 
 int /*<<< orphan*/  ShouldCompress (int const*,size_t const,int /*<<< orphan*/  const,size_t const,size_t const,size_t const) ; 
 int /*<<< orphan*/  WrapPosition (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static void WriteMetaBlockInternal(MemoryManager* m,
                                   const uint8_t* data,
                                   const size_t mask,
                                   const uint64_t last_flush_pos,
                                   const size_t bytes,
                                   const BROTLI_BOOL is_last,
                                   ContextType literal_context_mode,
                                   const BrotliEncoderParams* params,
                                   const uint8_t prev_byte,
                                   const uint8_t prev_byte2,
                                   const size_t num_literals,
                                   const size_t num_commands,
                                   Command* commands,
                                   const int* saved_dist_cache,
                                   int* dist_cache,
                                   size_t* storage_ix,
                                   uint8_t* storage) {
  const uint32_t wrapped_last_flush_pos = WrapPosition(last_flush_pos);
  uint16_t last_bytes;
  uint8_t last_bytes_bits;
  ContextLut literal_context_lut = BROTLI_CONTEXT_LUT(literal_context_mode);
  BrotliEncoderParams block_params = *params;

  if (bytes == 0) {
    /* Write the ISLAST and ISEMPTY bits. */
    BrotliWriteBits(2, 3, storage_ix, storage);
    *storage_ix = (*storage_ix + 7u) & ~7u;
    return;
  }

  if (!ShouldCompress(data, mask, last_flush_pos, bytes,
                      num_literals, num_commands)) {
    /* Restore the distance cache, as its last update by
       CreateBackwardReferences is now unused. */
    memcpy(dist_cache, saved_dist_cache, 4 * sizeof(dist_cache[0]));
    BrotliStoreUncompressedMetaBlock(is_last, data,
                                     wrapped_last_flush_pos, mask, bytes,
                                     storage_ix, storage);
    return;
  }

  BROTLI_DCHECK(*storage_ix <= 14);
  last_bytes = (uint16_t)((storage[1] << 8) | storage[0]);
  last_bytes_bits = (uint8_t)(*storage_ix);
  if (params->quality <= MAX_QUALITY_FOR_STATIC_ENTROPY_CODES) {
    BrotliStoreMetaBlockFast(m, data, wrapped_last_flush_pos,
                             bytes, mask, is_last, params,
                             commands, num_commands,
                             storage_ix, storage);
    if (BROTLI_IS_OOM(m)) return;
  } else if (params->quality < MIN_QUALITY_FOR_BLOCK_SPLIT) {
    BrotliStoreMetaBlockTrivial(m, data, wrapped_last_flush_pos,
                                bytes, mask, is_last, params,
                                commands, num_commands,
                                storage_ix, storage);
    if (BROTLI_IS_OOM(m)) return;
  } else {
    MetaBlockSplit mb;
    InitMetaBlockSplit(&mb);
    if (params->quality < MIN_QUALITY_FOR_HQ_BLOCK_SPLITTING) {
      size_t num_literal_contexts = 1;
      const uint32_t* literal_context_map = NULL;
      if (!params->disable_literal_context_modeling) {
        DecideOverLiteralContextModeling(
            data, wrapped_last_flush_pos, bytes, mask, params->quality,
            params->size_hint, &num_literal_contexts,
            &literal_context_map);
      }
      BrotliBuildMetaBlockGreedy(m, data, wrapped_last_flush_pos, mask,
          prev_byte, prev_byte2, literal_context_lut, num_literal_contexts,
          literal_context_map, commands, num_commands, &mb);
      if (BROTLI_IS_OOM(m)) return;
    } else {
      BrotliBuildMetaBlock(m, data, wrapped_last_flush_pos, mask, &block_params,
                           prev_byte, prev_byte2,
                           commands, num_commands,
                           literal_context_mode,
                           &mb);
      if (BROTLI_IS_OOM(m)) return;
    }
    if (params->quality >= MIN_QUALITY_FOR_OPTIMIZE_HISTOGRAMS) {
      /* The number of distance symbols effectively used for distance
         histograms. It might be less than distance alphabet size
         for "Large Window Brotli" (32-bit). */
      BrotliOptimizeHistograms(block_params.dist.alphabet_size_limit, &mb);
    }
    BrotliStoreMetaBlock(m, data, wrapped_last_flush_pos, bytes, mask,
                         prev_byte, prev_byte2,
                         is_last,
                         &block_params,
                         literal_context_mode,
                         commands, num_commands,
                         &mb,
                         storage_ix, storage);
    if (BROTLI_IS_OOM(m)) return;
    DestroyMetaBlockSplit(m, &mb);
  }
  if (bytes + 4 < (*storage_ix >> 3)) {
    /* Restore the distance cache and last byte. */
    memcpy(dist_cache, saved_dist_cache, 4 * sizeof(dist_cache[0]));
    storage[0] = (uint8_t)last_bytes;
    storage[1] = (uint8_t)(last_bytes >> 8);
    *storage_ix = last_bytes_bits;
    BrotliStoreUncompressedMetaBlock(is_last, data,
                                     wrapped_last_flush_pos, mask,
                                     bytes, storage_ix, storage);
  }
}