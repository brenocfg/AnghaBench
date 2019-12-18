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
struct video_viewport {int dummy; } ;
struct TYPE_2__ {struct video_viewport vp; } ;
typedef  TYPE_1__ switch_video_t ;

/* Variables and functions */

__attribute__((used)) static void switch_viewport_info(void *data, struct video_viewport *vp)
{
   switch_video_t *sw = data;
   *vp = sw->vp;
}