#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* e; void* rw; void* rs; } ;

/* Variables and functions */
 void* BIT_CLR ; 
 void* BIT_SET ; 
 TYPE_1__ bits ; 
 scalar_t__ lcd_addr_x ; 
 scalar_t__ lcd_addr_y ; 
 int /*<<< orphan*/  lcd_gotoxy () ; 
 int lcd_height ; 
 int lcd_hwidth ; 
 int /*<<< orphan*/  pprt ; 
 int /*<<< orphan*/  pprt_lock ; 
 int /*<<< orphan*/  set_ctrl_bits () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w_dtr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void lcd_clear_fast_p8(void)
{
	int pos;
	lcd_addr_x = lcd_addr_y = 0;
	lcd_gotoxy();

	spin_lock(&pprt_lock);
	for (pos = 0; pos < lcd_height * lcd_hwidth; pos++) {
		/* present the data to the data port */
		w_dtr(pprt, ' ');
		udelay(20);	/* maintain the data during 20 us before the strobe */

		bits.e = BIT_SET;
		bits.rs = BIT_SET;
		bits.rw = BIT_CLR;
		set_ctrl_bits();

		udelay(40);	/* maintain the strobe during 40 us */

		bits.e = BIT_CLR;
		set_ctrl_bits();

		udelay(45);	/* the shortest data takes at least 45 us */
	}
	spin_unlock(&pprt_lock);

	lcd_addr_x = lcd_addr_y = 0;
	lcd_gotoxy();
}