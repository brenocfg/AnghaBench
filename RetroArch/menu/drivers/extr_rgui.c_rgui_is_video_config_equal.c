#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ width; scalar_t__ height; scalar_t__ x; scalar_t__ y; } ;
struct TYPE_6__ {scalar_t__ aspect_ratio_idx; TYPE_1__ viewport; } ;
typedef  TYPE_2__ rgui_video_settings_t ;

/* Variables and functions */

bool rgui_is_video_config_equal(rgui_video_settings_t *config_a, rgui_video_settings_t *config_b)
{
   return (config_a->aspect_ratio_idx == config_b->aspect_ratio_idx) &&
          (config_a->viewport.width == config_b->viewport.width) &&
          (config_a->viewport.height == config_b->viewport.height) &&
          (config_a->viewport.x == config_b->viewport.x) &&
          (config_a->viewport.y == config_b->viewport.y);
}