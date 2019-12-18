#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  context_data; int /*<<< orphan*/  (* cb_swap_buffers ) (int /*<<< orphan*/ ,TYPE_1__*) ;int /*<<< orphan*/  runloop_is_paused; int /*<<< orphan*/  runloop_is_slowmotion; int /*<<< orphan*/  input_driver_nonblock_state; scalar_t__ black_frame_insertion; } ;
typedef  TYPE_1__ video_frame_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_REINIT ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  RWebAudioRecalibrateTime () ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emscripten_force_exit (int /*<<< orphan*/ ) ; 
 int emscripten_frame_count ; 
 scalar_t__ emscripten_fullscreen_reinit ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_exit (int /*<<< orphan*/ *) ; 
 int runloop_iterate () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  task_queue_check () ; 
 int /*<<< orphan*/  video_driver_build_info (TYPE_1__*) ; 

__attribute__((used)) static void emscripten_mainloop(void)
{
   int ret;
   video_frame_info_t video_info;

   RWebAudioRecalibrateTime();

   emscripten_frame_count++;

   video_driver_build_info(&video_info);

   /* Disable BFI during fast forward, slow-motion,
    * and pause to prevent flicker. */
   if (
         video_info.black_frame_insertion
         && !video_info.input_driver_nonblock_state
         && !video_info.runloop_is_slowmotion
         && !video_info.runloop_is_paused)
   {
      if ((emscripten_frame_count & 1) == 0)
      {
         glClear(GL_COLOR_BUFFER_BIT);
         video_info.cb_swap_buffers(video_info.context_data, &video_info);
         return;
      }
   }

   if (emscripten_fullscreen_reinit != 0)
   {
      if (--emscripten_fullscreen_reinit == 0)
         command_event(CMD_EVENT_REINIT, NULL);
   }

   ret = runloop_iterate();

   task_queue_check();

   if (ret != -1)
      return;

   main_exit(NULL);
   emscripten_force_exit(0);
}