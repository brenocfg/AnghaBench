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
 int /*<<< orphan*/  emu_status_msg (char*) ; 
 int /*<<< orphan*/  pemu_finalize_frame (char*,char const*) ; 
 int /*<<< orphan*/  plat_status_msg_clear () ; 
 int /*<<< orphan*/  plat_video_flip () ; 
 int reset_timing ; 

void plat_status_msg_busy_next(const char *msg)
{
	plat_status_msg_clear();
	pemu_finalize_frame("", msg);
	plat_video_flip();
	emu_status_msg("");
	reset_timing = 1;
}