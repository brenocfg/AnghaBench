#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int video_windowed_fullscreen; } ;
struct TYPE_5__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 TYPE_2__* config_get_ptr () ; 

__attribute__((used)) static bool d3d8_is_windowed_enable(bool info_fullscreen)
{
#ifndef _XBOX
   settings_t *settings = config_get_ptr();
   if (!info_fullscreen)
      return true;
   if (settings)
      return settings->bools.video_windowed_fullscreen;
#endif
   return false;
}