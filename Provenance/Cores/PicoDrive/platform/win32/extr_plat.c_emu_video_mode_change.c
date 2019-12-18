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
struct TYPE_2__ {int left; int right; int top; int bottom; } ;

/* Variables and functions */
 TYPE_1__ EmuScreenRect ; 
 int /*<<< orphan*/  FrameWnd ; 
 int /*<<< orphan*/  PostMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_COMMAND ; 

void emu_video_mode_change(int start_line, int line_count, int is_32cols)
{
	EmuScreenRect.left = is_32cols ? 32 : 0;
	EmuScreenRect.right = is_32cols ? 256+32 : 320;
	EmuScreenRect.top = start_line;
	EmuScreenRect.bottom = start_line + line_count;

	PostMessage(FrameWnd, WM_COMMAND, 0x20000 | 2000, 0);
}