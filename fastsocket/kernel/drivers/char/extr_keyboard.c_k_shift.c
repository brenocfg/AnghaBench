#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int dummy; } ;
struct TYPE_3__ {scalar_t__ kbdmode; } ;

/* Variables and functions */
 unsigned char KVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  K_CAPSSHIFT ; 
 int /*<<< orphan*/  K_SHIFT ; 
 int /*<<< orphan*/  VC_CAPSLOCK ; 
 scalar_t__ VC_UNICODE ; 
 int /*<<< orphan*/  clr_vc_kbd_led (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kbd ; 
 int npadch ; 
 int /*<<< orphan*/  put_queue (struct vc_data*,int) ; 
 scalar_t__ rep ; 
 scalar_t__* shift_down ; 
 int shift_state ; 
 int /*<<< orphan*/  to_utf8 (struct vc_data*,int) ; 

__attribute__((used)) static void k_shift(struct vc_data *vc, unsigned char value, char up_flag)
{
	int old_state = shift_state;

	if (rep)
		return;
	/*
	 * Mimic typewriter:
	 * a CapsShift key acts like Shift but undoes CapsLock
	 */
	if (value == KVAL(K_CAPSSHIFT)) {
		value = KVAL(K_SHIFT);
		if (!up_flag)
			clr_vc_kbd_led(kbd, VC_CAPSLOCK);
	}

	if (up_flag) {
		/*
		 * handle the case that two shift or control
		 * keys are depressed simultaneously
		 */
		if (shift_down[value])
			shift_down[value]--;
	} else
		shift_down[value]++;

	if (shift_down[value])
		shift_state |= (1 << value);
	else
		shift_state &= ~(1 << value);

	/* kludge */
	if (up_flag && shift_state != old_state && npadch != -1) {
		if (kbd->kbdmode == VC_UNICODE)
			to_utf8(vc, npadch);
		else
			put_queue(vc, npadch & 0xff);
		npadch = -1;
	}
}