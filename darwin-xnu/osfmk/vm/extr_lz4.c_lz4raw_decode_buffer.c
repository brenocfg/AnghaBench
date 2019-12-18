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

/* Variables and functions */
 size_t LZ4_GOFAST_SAFETY_MARGIN ; 
 scalar_t__ lz4_decode (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 scalar_t__ lz4_decode_asm (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 

size_t lz4raw_decode_buffer(uint8_t * __restrict dst_buffer, size_t dst_size,
                            const uint8_t * __restrict src_buffer, size_t src_size,
                            void * __restrict work __attribute__((unused)))
{
  const uint8_t * src = src_buffer;
  uint8_t * dst = dst_buffer;
  
  // Go fast if we can, keeping away from the end of buffers
#if LZ4_ENABLE_ASSEMBLY_DECODE
  if (dst_size > LZ4_GOFAST_SAFETY_MARGIN && src_size > LZ4_GOFAST_SAFETY_MARGIN)
  {
    if (lz4_decode_asm(&dst, dst_buffer, dst_buffer + dst_size - LZ4_GOFAST_SAFETY_MARGIN, &src, src_buffer + src_size - LZ4_GOFAST_SAFETY_MARGIN))
      return 0; // FAIL
  }
#endif
//DRKTODO: Can the 'C' "safety" decode be eliminated for 4/16K fixed-sized buffers?
  
  // Finish safe
  if (lz4_decode(&dst, dst_buffer, dst_buffer + dst_size, &src, src_buffer + src_size))
    return 0; // FAIL

  return (size_t)(dst - dst_buffer); // bytes produced
}