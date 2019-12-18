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
struct video_ortho {int member_1; int member_3; int member_4; int member_5; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {unsigned int dev_rotation; } ;
typedef  TYPE_1__ d3d9_video_t ;

/* Variables and functions */

__attribute__((used)) static void d3d9_set_rotation(void *data, unsigned rot)
{
   d3d9_video_t        *d3d = (d3d9_video_t*)data;
   struct video_ortho ortho = {0, 1, 0, 1, -1, 1};

   if (!d3d)
      return;

   d3d->dev_rotation = rot;
}