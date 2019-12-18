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
 int /*<<< orphan*/  PicoDrawSetOutBuf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vout_buf ; 
 int vout_height ; 
 int vout_offset ; 
 int vout_width ; 

void emu_video_mode_change(int start_line, int line_count, int is_32cols)
{
	memset(vout_buf, 0, 320 * 240 * 2);
	vout_width = is_32cols ? 256 : 320;
	PicoDrawSetOutBuf(vout_buf, vout_width * 2);

	vout_height = line_count;
	vout_offset = vout_width * start_line;
}