#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int offset; int word; } ;
typedef  TYPE_1__ lz4_hash_entry_t ;

/* Variables and functions */
 int LZ4_COMPRESS_HASH_ENTRIES ; 
 int /*<<< orphan*/  lz4_encode_2gb (int /*<<< orphan*/ **,size_t,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,size_t const,TYPE_1__*,int) ; 

size_t lz4raw_encode_buffer(uint8_t * __restrict dst_buffer, size_t dst_size,
                            const uint8_t * __restrict src_buffer, size_t src_size,
                            lz4_hash_entry_t hash_table[LZ4_COMPRESS_HASH_ENTRIES])
{
  //  Initialize hash table
  const lz4_hash_entry_t HASH_FILL = { .offset = 0x80000000, .word = 0x0 };
  
  const uint8_t * src = src_buffer;
  uint8_t * dst = dst_buffer;
  
  // We need several blocks because our base function is limited to 2GB input
  const size_t BLOCK_SIZE = 0x7ffff000;
  while (src_size > 0)
  {
	  //DRKTODO either implement pattern4 or figure out optimal unroll
	  //DRKTODO: bizarrely, with plain O3 the compiler generates a single
	  //DRKTODO: scalar STP per loop iteration with the stock loop
	  //DRKTODO If hand unrolled, it switches to NEON store pairs
    // Reset hash table for each block
/* #if __STDC_HOSTED__ */
/*     memset_pattern8(hash_table, &HASH_FILL, lz4_encode_scratch_size); */
/* #else */
/*     for (int i=0;i<LZ4_COMPRESS_HASH_ENTRIES;i++) hash_table[i] = HASH_FILL; */
/* #endif */

    	  for (int i=0;i<LZ4_COMPRESS_HASH_ENTRIES;) {
		  hash_table[i++] = HASH_FILL;
		  hash_table[i++] = HASH_FILL;
		  hash_table[i++] = HASH_FILL;
		  hash_table[i++] = HASH_FILL;
	  }

    // Bytes to encode in this block
    const size_t src_to_encode = src_size > BLOCK_SIZE ? BLOCK_SIZE : src_size;
    
    // Run the encoder, only the last block emits final literals. Allows concatenation of encoded payloads.
    // Blocks are encoded independently, so src_begin is set to each block origin instead of src_buffer
    uint8_t * dst_start = dst;
    const uint8_t * src_start = src;
    lz4_encode_2gb(&dst, dst_size, &src, src, src_to_encode, hash_table, src_to_encode < src_size);
    
    // Check progress
    size_t dst_used = dst - dst_start;
    size_t src_used = src - src_start; // src_used <= src_to_encode
    if (src_to_encode == src_size && src_used < src_to_encode) return 0; // FAIL to encode last block

    // Note that there is a potential problem here in case of non compressible data requiring more blocks.
    // We may end up here with src_used very small, or even 0, and will not be able to make progress during
    // compression. We FAIL unless the length of literals remaining at the end is small enough.
    if (src_to_encode < src_size && src_to_encode - src_used >= (1<<16)) return 0; // FAIL too many literals
    
    // Update counters (SRC and DST already have been updated)
    src_size -= src_used;
    dst_size -= dst_used;
  }

  return (size_t)(dst - dst_buffer); // bytes produced
}