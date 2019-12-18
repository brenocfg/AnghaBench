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
struct video_viewport {int dummy; } ;
typedef  int /*<<< orphan*/  d3d8_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d8_renderchain_viewport_info (int /*<<< orphan*/ *,struct video_viewport*) ; 

__attribute__((used)) static void d3d8_viewport_info(void *data, struct video_viewport *vp)
{
   d3d8_video_t *d3d   = (d3d8_video_t*)data;

   if (d3d)
      d3d8_renderchain_viewport_info(d3d, vp);
}