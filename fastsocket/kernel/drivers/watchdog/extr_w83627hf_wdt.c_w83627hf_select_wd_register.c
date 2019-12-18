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
 int /*<<< orphan*/  WDT_EFDR ; 
 int /*<<< orphan*/  WDT_EFER ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w83627hf_select_wd_register(void)
{
	unsigned char c;
	outb_p(0x87, WDT_EFER); /* Enter extended function mode */
	outb_p(0x87, WDT_EFER); /* Again according to manual */

	outb(0x20, WDT_EFER);	/* check chip version	*/
	c = inb(WDT_EFDR);
	if (c == 0x82) {	/* W83627THF		*/
		outb_p(0x2b, WDT_EFER); /* select GPIO3 */
		c = ((inb_p(WDT_EFDR) & 0xf7) | 0x04); /* select WDT0 */
		outb_p(0x2b, WDT_EFER);
		outb_p(c, WDT_EFDR);	/* set GPIO3 to WDT0 */
	} else if (c == 0x88) {	/* W83627EHF */
		outb_p(0x2d, WDT_EFER); /* select GPIO5 */
		c = inb_p(WDT_EFDR) & ~0x01; /* PIN77 -> WDT0# */
		outb_p(0x2d, WDT_EFER);
		outb_p(c, WDT_EFDR); /* set GPIO5 to WDT0 */
	}

	outb_p(0x07, WDT_EFER); /* point to logical device number reg */
	outb_p(0x08, WDT_EFDR); /* select logical device 8 (GPIO2) */
	outb_p(0x30, WDT_EFER); /* select CR30 */
	outb_p(0x01, WDT_EFDR); /* set bit 0 to activate GPIO2 */
}