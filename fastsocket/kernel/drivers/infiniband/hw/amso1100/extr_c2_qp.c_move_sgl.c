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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct ib_sge {scalar_t__ length; scalar_t__ lkey; int /*<<< orphan*/  addr; } ;
struct c2_data_addr {void* length; scalar_t__ to; void* stag; } ;

/* Variables and functions */
 int EINVAL ; 
 void* cpu_to_be32 (scalar_t__) ; 
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
move_sgl(struct c2_data_addr * dst, struct ib_sge *src, int count, u32 * p_len,
	 u8 * actual_count)
{
	u32 tot = 0;		/* running total */
	u8 acount = 0;		/* running total non-0 len sge's */

	while (count > 0) {
		/*
		 * If the addition of this SGE causes the
		 * total SGL length to exceed 2^32-1, then
		 * fail-n-bail.
		 *
		 * If the current total plus the next element length
		 * wraps, then it will go negative and be less than the
		 * current total...
		 */
		if ((tot + src->length) < tot) {
			return -EINVAL;
		}
		/*
		 * Bug: 1456 (as well as 1498 & 1643)
		 * Skip over any sge's supplied with len=0
		 */
		if (src->length) {
			tot += src->length;
			dst->stag = cpu_to_be32(src->lkey);
			dst->to = cpu_to_be64(src->addr);
			dst->length = cpu_to_be32(src->length);
			dst++;
			acount++;
		}
		src++;
		count--;
	}

	if (acount == 0) {
		/*
		 * Bug: 1476 (as well as 1498, 1456 and 1643)
		 * Setup the SGL in the WR to make it easier for the RNIC.
		 * This way, the FW doesn't have to deal with special cases.
		 * Setting length=0 should be sufficient.
		 */
		dst->stag = 0;
		dst->to = 0;
		dst->length = 0;
	}

	*p_len = tot;
	*actual_count = acount;
	return 0;
}