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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/ * crc_stream ;

/* Variables and functions */
 int LONG_SHIFT ; 
 int SHORT_SHIFT ; 
 int _mm_crc32_u32 (int,int const) ; 
 int _mm_crc32_u64 (int,int /*<<< orphan*/ ) ; 
 int _mm_crc32_u8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  long_shifts ; 
 int shift_crc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  short_shifts ; 

uint32_t crc32c_hw(uint32_t crc, crc_stream buf, size_t len) {
  crc_stream next = buf;
  crc_stream end;
#ifdef _M_X64
  uint64_t crc0, crc1, crc2; /* need to be 64 bits for crc32q */
#else
  uint32_t crc0, crc1, crc2;
#endif

  /* pre-process the crc */
  crc0 = crc ^ 0xffffffff;

  /* compute the crc for up to seven leading bytes to bring the data pointer
     to an eight-byte boundary */
  while (len && ((uintptr_t)next & 7) != 0) {
    crc0 = _mm_crc32_u8((uint32_t)(crc0), *next);
    ++next;
    --len;
  }

#ifdef _M_X64
  /* compute the crc on sets of LONG_SHIFT*3 bytes, executing three independent
     crc
     instructions, each on LONG_SHIFT bytes -- this is optimized for the
     Nehalem,
     Westmere, Sandy Bridge, and Ivy Bridge architectures, which have a
     throughput of one crc per cycle, but a latency of three cycles */
  while (len >= 3 * LONG_SHIFT) {
    crc1 = 0;
    crc2 = 0;
    end = next + LONG_SHIFT;
    do {
      crc0 = _mm_crc32_u64(crc0, *(uint64_t *)(next));
      crc1 = _mm_crc32_u64(crc1, *(uint64_t *)(next + LONG_SHIFT));
      crc2 = _mm_crc32_u64(crc2, *(uint64_t *)(next + 2 * LONG_SHIFT));
      next += 8;
    } while (next < end);
    crc0 = shift_crc(long_shifts, (uint32_t)(crc0)) ^ crc1;
    crc0 = shift_crc(long_shifts, (uint32_t)(crc0)) ^ crc2;
    next += 2 * LONG_SHIFT;
    len -= 3 * LONG_SHIFT;
  }

  /* do the same thing, but now on SHORT_SHIFT*3 blocks for the remaining data
     less
     than a LONG_SHIFT*3 block */
  while (len >= 3 * SHORT_SHIFT) {
    crc1 = 0;
    crc2 = 0;
    end = next + SHORT_SHIFT;
    do {
      crc0 = _mm_crc32_u64(crc0, *(uint64_t *)(next));
      crc1 = _mm_crc32_u64(crc1, *(uint64_t *)(next + SHORT_SHIFT));
      crc2 = _mm_crc32_u64(crc2, *(uint64_t *)(next + 2 * SHORT_SHIFT));
      next += 8;
    } while (next < end);
    crc0 = shift_crc(short_shifts, (uint32_t)(crc0)) ^ crc1;
    crc0 = shift_crc(short_shifts, (uint32_t)(crc0)) ^ crc2;
    next += 2 * SHORT_SHIFT;
    len -= 3 * SHORT_SHIFT;
  }

  /* compute the crc on the remaining eight-byte units less than a SHORT_SHIFT*3
   * block */
  end = next + (len - (len & 7));
  while (next < end) {
    crc0 = _mm_crc32_u64(crc0, *(uint64_t *)(next));
    next += 8;
  }
#else
  /* compute the crc on sets of LONG_SHIFT*3 bytes, executing three independent
     crc
     instructions, each on LONG_SHIFT bytes -- this is optimized for the
     Nehalem,
     Westmere, Sandy Bridge, and Ivy Bridge architectures, which have a
     throughput of one crc per cycle, but a latency of three cycles */
  while (len >= 3 * LONG_SHIFT) {
    crc1 = 0;
    crc2 = 0;
    end = next + LONG_SHIFT;
    do {
      crc0 = _mm_crc32_u32(crc0, *(uint32_t *)(next));
      crc1 = _mm_crc32_u32(crc1, *(const uint32_t *)(next + LONG_SHIFT));
      crc2 = _mm_crc32_u32(crc2, *(const uint32_t *)(next + 2 * LONG_SHIFT));
      next += 4;
    } while (next < end);
    crc0 = shift_crc(long_shifts, (uint32_t)(crc0)) ^ crc1;
    crc0 = shift_crc(long_shifts, (uint32_t)(crc0)) ^ crc2;
    next += 2 * LONG_SHIFT;
    len -= 3 * LONG_SHIFT;
  }

  /* do the same thing, but now on SHORT_SHIFT*3 blocks for the remaining data
     less
     than a LONG_SHIFT*3 block */
  while (len >= 3 * SHORT_SHIFT) {
    crc1 = 0;
    crc2 = 0;
    end = next + SHORT_SHIFT;
    do {
      crc0 = _mm_crc32_u32(crc0, *(const uint32_t *)(next));
      crc1 = _mm_crc32_u32(crc1, *(const uint32_t *)(next + SHORT_SHIFT));
      crc2 = _mm_crc32_u32(crc2, *(const uint32_t *)(next + 2 * SHORT_SHIFT));
      next += 4;
    } while (next < end);
    crc0 = shift_crc(short_shifts, (uint32_t)(crc0)) ^ crc1;
    crc0 = shift_crc(short_shifts, (uint32_t)(crc0)) ^ crc2;
    next += 2 * SHORT_SHIFT;
    len -= 3 * SHORT_SHIFT;
  }

  /* compute the crc on the remaining eight-byte units less than a SHORT_SHIFT*3
     block */
  end = next + (len - (len & 7));
  while (next < end) {
    crc0 = _mm_crc32_u32(crc0, *(const uint32_t *)(next));
    next += 4;
  }
#endif
  len &= 7;

  /* compute the crc for up to seven trailing bytes */
  while (len) {
    crc0 = _mm_crc32_u8((uint32_t)(crc0), *next);
    ++next;
    --len;
  }

  /* return a post-processed crc */
  return (uint32_t)(crc0) ^ 0xffffffff;
}