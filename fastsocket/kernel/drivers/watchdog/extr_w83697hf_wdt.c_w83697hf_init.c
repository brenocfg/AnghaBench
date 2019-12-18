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
 int /*<<< orphan*/  w83697hf_deselect_wdt () ; 
 unsigned char w83697hf_get_reg (int) ; 
 int /*<<< orphan*/  w83697hf_select_wdt () ; 
 int /*<<< orphan*/  w83697hf_set_reg (int,unsigned char) ; 

__attribute__((used)) static void w83697hf_init(void)
{
	unsigned char bbuf;

	w83697hf_select_wdt();

	bbuf = w83697hf_get_reg(0x29);
	bbuf &= ~0x60;
	bbuf |= 0x20;

	/* Set pin 119 to WDTO# mode (= CR29, WDT0) */
	w83697hf_set_reg(0x29, bbuf);

	bbuf = w83697hf_get_reg(0xF3);
	bbuf &= ~0x04;
	w83697hf_set_reg(0xF3, bbuf);	/* Count mode is seconds */

	w83697hf_deselect_wdt();
}