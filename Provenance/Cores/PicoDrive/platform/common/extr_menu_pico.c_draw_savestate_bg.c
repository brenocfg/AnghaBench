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
 int /*<<< orphan*/  PicoStateLoadGfx (char const*) ; 
 int /*<<< orphan*/  PicoTmpStateRestore (void*) ; 
 void* PicoTmpStateSave () ; 
 char* emu_get_save_fname (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_bg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pemu_forced_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_savestate_bg(int slot)
{
	const char *fname;
	void *tmp_state;

	fname = emu_get_save_fname(1, 0, slot, NULL);
	if (!fname)
		return;

	tmp_state = PicoTmpStateSave();

	PicoStateLoadGfx(fname);

	/* do a frame and fetch menu bg */
	pemu_forced_frame(0, 0);

	make_bg(0);

	PicoTmpStateRestore(tmp_state);
}