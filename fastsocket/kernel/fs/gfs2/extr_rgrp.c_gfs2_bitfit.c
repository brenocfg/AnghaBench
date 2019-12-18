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
typedef  unsigned char u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct gfs2_bitmap {int bi_len; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int BFITNOENT ; 
 int GFS2_NBBY ; 
 int __ffs64 (int) ; 
 int gfs2_bit_search (int /*<<< orphan*/  const*,int,unsigned char) ; 

__attribute__((used)) static u32 gfs2_bitfit(const u8 *buf, struct gfs2_bitmap *bi, u32 goal,
		       u8 state)
{
	u32 spoint = (goal << 1) & ((8*sizeof(u64)) - 1);
	const __le64 *ptr = ((__le64 *)buf) + (goal >> 5);
	const __le64 *end = (__le64 *)(buf + ALIGN(bi->bi_len, sizeof(u64)));
	u64 tmp;
	u64 mask = 0x5555555555555555ULL;
	u32 bit;

	/* Mask off bits we don't care about at the start of the search */
	mask <<= spoint;
	tmp = gfs2_bit_search(ptr, mask, state);
	ptr++;
	while(tmp == 0 && ptr < end) {
		tmp = gfs2_bit_search(ptr, 0x5555555555555555ULL, state);
		ptr++;
	}
	/* Mask off any bits which are more than len bytes from the start */
	if (ptr == end && (bi->bi_len & (sizeof(u64) - 1)))
		tmp &= (((u64)~0) >> (64 - 8*(bi->bi_len & (sizeof(u64) - 1))));
	if (tmp == 0)
		return BFITNOENT;
	ptr--;
	bit = __ffs64(tmp);
	bit /= 2;	/* two bits per entry in the bitmap */
	return (((const unsigned char *)ptr - buf) * GFS2_NBBY) + bit;
}