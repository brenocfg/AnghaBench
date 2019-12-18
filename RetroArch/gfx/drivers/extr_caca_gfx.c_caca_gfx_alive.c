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
 int /*<<< orphan*/  caca_video_height ; 
 int /*<<< orphan*/  caca_video_width ; 
 int /*<<< orphan*/  video_driver_set_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool caca_gfx_alive(void *data)
{
   (void)data;
   video_driver_set_size(&caca_video_width, &caca_video_height);
   return true;
}