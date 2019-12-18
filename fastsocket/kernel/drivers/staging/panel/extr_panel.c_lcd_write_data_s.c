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

/* Variables and functions */
 int /*<<< orphan*/  lcd_send_serial (int) ; 
 int /*<<< orphan*/  pprt_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lcd_write_data_s(int data)
{
	spin_lock(&pprt_lock);
	lcd_send_serial(0x5F);	/* R/W=W, RS=1 */
	lcd_send_serial(data & 0x0F);
	lcd_send_serial((data >> 4) & 0x0F);
	udelay(40);		/* the shortest data takes at least 40 us */
	spin_unlock(&pprt_lock);
}