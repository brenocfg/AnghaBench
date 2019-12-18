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
 int /*<<< orphan*/  out_byte (int) ; 
 int /*<<< orphan*/  start () ; 
 int /*<<< orphan*/  stop () ; 

__attribute__((used)) static void
ds1302_wdisable(void) 
{
	start();
	out_byte(0x8e); /* Write control register  */
	out_byte(0x80); /* Disable write protect bit 7 = 0 */
	stop();
}