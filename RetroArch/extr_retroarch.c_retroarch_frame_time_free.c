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
struct retro_frame_time_callback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  runloop_frame_time ; 
 scalar_t__ runloop_frame_time_last ; 
 scalar_t__ runloop_max_frames ; 

__attribute__((used)) static void retroarch_frame_time_free(void)
{
   memset(&runloop_frame_time, 0,
         sizeof(struct retro_frame_time_callback));
   runloop_frame_time_last           = 0;
   runloop_max_frames                = 0;
}