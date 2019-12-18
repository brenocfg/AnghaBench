#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dirtyPal; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  PicoDrawSetCallbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PicoDrawSetOutBuf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_cmn_forced_frame (int,int) ; 
 int /*<<< orphan*/  g_menubg_src_ptr ; 
 int /*<<< orphan*/  g_screen_ptr ; 
 int g_screen_width ; 

void pemu_forced_frame(int no_scale, int do_emu)
{
	PicoDrawSetOutBuf(g_screen_ptr, g_screen_width * 2);
	PicoDrawSetCallbacks(NULL, NULL);
	Pico.m.dirtyPal = 1;

	emu_cmn_forced_frame(no_scale, do_emu);

	g_menubg_src_ptr = g_screen_ptr;
}