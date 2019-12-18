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
 int /*<<< orphan*/  dummy_frame_buf ; 
 int /*<<< orphan*/  dummy_input_poll_cb () ; 
 int /*<<< orphan*/  dummy_video_cb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  frame_buf_height ; 
 int frame_buf_width ; 

void libretro_dummy_retro_run(void)
{
   dummy_input_poll_cb();
   dummy_video_cb(dummy_frame_buf, frame_buf_width, frame_buf_height, 2 * frame_buf_width);
}