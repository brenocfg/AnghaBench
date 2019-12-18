#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int EmuOpt; } ;

/* Variables and functions */
 scalar_t__ GetTickCount () ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  emu_text_out16 (int,int,char const*) ; 
 int /*<<< orphan*/ * fb_lock (int) ; 
 int /*<<< orphan*/  fb_unlock () ; 
 int /*<<< orphan*/ * giz_screen ; 
 int /*<<< orphan*/  memset32 (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ noticeMsgTime ; 
 int reset_timing ; 

__attribute__((used)) static void emu_msg_cb(const char *msg)
{
	if (giz_screen != NULL) fb_unlock();
	giz_screen = fb_lock(1);

	memset32((int *)((char *)giz_screen + 321*232*2), 0, 321*8*2/4);
	emu_text_out16(4, 232, msg);
	noticeMsgTime = GetTickCount() - 2000;

	/* assumption: emu_msg_cb gets called only when something slow is about to happen */
	reset_timing = 1;

	fb_unlock();
	giz_screen = fb_lock((currentConfig.EmuOpt&0x8000) ? 0 : 1);
}