#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int keep_aspect; int o_size; int should_resize; } ;
typedef  TYPE_2__ switch_video_t ;
struct TYPE_5__ {int /*<<< orphan*/  video_scale_integer; } ;
struct TYPE_7__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;

/* Variables and functions */
#define  ASPECT_RATIO_CORE 129 
#define  ASPECT_RATIO_CUSTOM 128 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  video_driver_set_viewport_core () ; 

__attribute__((used)) static void switch_set_aspect_ratio(void *data, unsigned aspect_ratio_idx)
{
    settings_t *settings = config_get_ptr();
    switch_video_t *sw   = (switch_video_t *)data;

    if (!sw)
        return;

    sw->keep_aspect      = true;
    sw->o_size           = false;

    switch (aspect_ratio_idx)
    {
       case ASPECT_RATIO_CORE:
          sw->o_size      = true;
          sw->keep_aspect = false;
          break;

       case ASPECT_RATIO_CUSTOM:
          if (settings->bools.video_scale_integer)
          {
             video_driver_set_viewport_core();
             sw->o_size      = true;
             sw->keep_aspect = false;
          }
          break;

       default:
          break;
    }


    sw->should_resize = true;
}