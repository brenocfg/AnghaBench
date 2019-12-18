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
struct usb_line6_pod {int /*<<< orphan*/  atomic_flags; scalar_t__ dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  POD_SAVE_PRESSED ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pod_save_button_pressed(struct usb_line6_pod *pod, int type, int index)
{
	pod->dirty = 0;
	set_bit(POD_SAVE_PRESSED, &pod->atomic_flags);
}