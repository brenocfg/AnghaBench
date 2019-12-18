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
struct mixart_mgr {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  MIXART_MEM (struct mixart_mgr*,scalar_t__) ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long jiffies ; 
 scalar_t__ readl_be (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static int mixart_wait_nice_for_register_value(struct mixart_mgr *mgr,
					       u32 offset, int is_egal,
					       u32 value, unsigned long timeout)
{
	unsigned long end_time = jiffies + (timeout * HZ / 100);
	u32 read;

	do {	/* we may take too long time in this loop.
		 * so give controls back to kernel if needed.
		 */
		cond_resched();

		read = readl_be( MIXART_MEM( mgr, offset ));
		if(is_egal) {
			if(read == value) return 0;
		}
		else { /* wait for different value */
			if(read != value) return 0;
		}
	} while ( time_after_eq(end_time, jiffies) );

	return -EBUSY;
}