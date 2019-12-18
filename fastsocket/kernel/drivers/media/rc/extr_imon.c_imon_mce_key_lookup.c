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
typedef  int u32 ;
struct imon_context {int rc_scancode; int release_code; int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int MCE_KEY_MASK ; 
 int MCE_TOGGLE_BIT ; 
 int rc_g_keycode_from_table (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 imon_mce_key_lookup(struct imon_context *ictx, u32 scancode)
{
	u32 keycode;

#define MCE_KEY_MASK 0x7000
#define MCE_TOGGLE_BIT 0x8000

	/*
	 * On some receivers, mce keys decode to 0x8000f04xx and 0x8000f84xx
	 * (the toggle bit flipping between alternating key presses), while
	 * on other receivers, we see 0x8000f74xx and 0x8000ff4xx. To keep
	 * the table trim, we always or in the bits to look up 0x8000ff4xx,
	 * but we can't or them into all codes, as some keys are decoded in
	 * a different way w/o the same use of the toggle bit...
	 */
	if (scancode & 0x80000000)
		scancode = scancode | MCE_KEY_MASK | MCE_TOGGLE_BIT;

	ictx->rc_scancode = scancode;
	keycode = rc_g_keycode_from_table(ictx->rdev, scancode);

	/* not used in mce mode, but make sure we know its false */
	ictx->release_code = false;

	return keycode;
}