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
typedef  scalar_t__ u32 ;
struct tg3 {int /*<<< orphan*/  (* read32 ) (struct tg3*,scalar_t__) ;int /*<<< orphan*/  (* write32 ) (struct tg3*,scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ICH_WORKAROUND ; 
 int /*<<< orphan*/  PCIX_TARGET_HWBUG ; 
 int /*<<< orphan*/  stub1 (struct tg3*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct tg3*,scalar_t__) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_write32 (struct tg3*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static void _tw32_flush(struct tg3 *tp, u32 off, u32 val, u32 usec_wait)
{
	if (tg3_flag(tp, PCIX_TARGET_HWBUG) || tg3_flag(tp, ICH_WORKAROUND))
		/* Non-posted methods */
		tp->write32(tp, off, val);
	else {
		/* Posted method */
		tg3_write32(tp, off, val);
		if (usec_wait)
			udelay(usec_wait);
		tp->read32(tp, off);
	}
	/* Wait again after the read for the posted method to guarantee that
	 * the wait time is met.
	 */
	if (usec_wait)
		udelay(usec_wait);
}