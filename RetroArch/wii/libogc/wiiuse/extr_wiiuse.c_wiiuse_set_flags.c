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
struct wiimote_t {int flags; } ;

/* Variables and functions */

int wiiuse_set_flags(struct wiimote_t* wm, int enable, int disable) {
	if (!wm)	return 0;

	/* remove mutually exclusive flags */
	enable &= ~disable;
	disable &= ~enable;

	wm->flags |= enable;
	wm->flags &= ~disable;

	return wm->flags;
}