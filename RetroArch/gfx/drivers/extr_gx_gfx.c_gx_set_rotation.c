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
struct TYPE_2__ {int should_resize; } ;
typedef  TYPE_1__ gx_video_t ;

/* Variables and functions */
 unsigned int g_orientation ; 

__attribute__((used)) static void gx_set_rotation(void *data, unsigned orientation)
{
   gx_video_t *gx = (gx_video_t*)data;
   g_orientation = orientation;

   if (gx)
      gx->should_resize = true;
}