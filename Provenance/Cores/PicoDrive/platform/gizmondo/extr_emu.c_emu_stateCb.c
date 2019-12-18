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
 int /*<<< orphan*/  Sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blit (char*,char const*) ; 
 int /*<<< orphan*/  clearArea (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fb_lock (int) ; 
 int /*<<< orphan*/  fb_unlock () ; 
 int /*<<< orphan*/ * giz_screen ; 

void emu_stateCb(const char *str)
{
	if (giz_screen != NULL) fb_unlock();
	giz_screen = fb_lock(1);

	clearArea(0);
	blit("", str);

	fb_unlock();
	giz_screen = NULL;

	Sleep(0); /* yield the CPU, the system may need it */
}