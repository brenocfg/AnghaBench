#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  quitting; } ;
typedef  TYPE_1__ sdl2_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  check_window (TYPE_1__*) ; 

__attribute__((used)) static bool sdl2_gfx_alive(void *data)
{
   sdl2_video_t *vid = (sdl2_video_t*)data;
   check_window(vid);
   return !vid->quitting;
}