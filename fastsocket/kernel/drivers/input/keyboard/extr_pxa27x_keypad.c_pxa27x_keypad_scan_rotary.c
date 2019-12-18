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
typedef  int uint32_t ;
struct pxa27x_keypad_platform_data {scalar_t__ enable_rotary1; scalar_t__ enable_rotary0; } ;
struct pxa27x_keypad {struct pxa27x_keypad_platform_data* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_KPREC ; 
 int /*<<< orphan*/  KPREC ; 
 int keypad_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keypad_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_rotary_event (struct pxa27x_keypad*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rotary_delta (int) ; 

__attribute__((used)) static void pxa27x_keypad_scan_rotary(struct pxa27x_keypad *keypad)
{
	struct pxa27x_keypad_platform_data *pdata = keypad->pdata;
	uint32_t kprec;

	/* read and reset to default count value */
	kprec = keypad_readl(KPREC);
	keypad_writel(KPREC, DEFAULT_KPREC);

	if (pdata->enable_rotary0)
		report_rotary_event(keypad, 0, rotary_delta(kprec));

	if (pdata->enable_rotary1)
		report_rotary_event(keypad, 1, rotary_delta(kprec >> 16));
}