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
struct m68k_serial {char* xmit_buf; int xmit_cnt; size_t xmit_tail; } ;

/* Variables and functions */
 int SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct m68k_serial* m68k_soft ; 
 int min (int,int) ; 
 int /*<<< orphan*/  rs_put_char (char) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rs_fair_output(void)
{
	int left;		/* Output no more than that */
	unsigned long flags;
	struct m68k_serial *info = &m68k_soft[0];
	char c;

	if (info == 0) return;
	if (info->xmit_buf == 0) return;

	local_irq_save(flags);
	left = info->xmit_cnt;
	while (left != 0) {
		c = info->xmit_buf[info->xmit_tail];
		info->xmit_tail = (info->xmit_tail+1) & (SERIAL_XMIT_SIZE-1);
		info->xmit_cnt--;
		local_irq_restore(flags);

		rs_put_char(c);

		local_irq_save(flags);
		left = min(info->xmit_cnt, left-1);
	}

	/* Last character is being transmitted now (hopefully). */
	udelay(5);

	local_irq_restore(flags);
	return;
}