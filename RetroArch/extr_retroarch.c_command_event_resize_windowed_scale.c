#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  video_fullscreen; } ;
struct TYPE_6__ {int /*<<< orphan*/  video_scale; } ;
struct TYPE_8__ {TYPE_2__ bools; TYPE_1__ floats; } ;
typedef  TYPE_3__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_REINIT ; 
 int /*<<< orphan*/  RARCH_CTL_SET_WINDOWED_SCALE ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configuration_set_float (TYPE_3__*,int /*<<< orphan*/ ,float) ; 
 TYPE_3__* configuration_settings ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,unsigned int*) ; 
 unsigned int runloop_pending_windowed_scale ; 

__attribute__((used)) static bool command_event_resize_windowed_scale(void)
{
   unsigned idx           = 0;
   settings_t *settings   = configuration_settings;
   unsigned window_scale  = runloop_pending_windowed_scale;

   if (window_scale == 0)
      return false;

   configuration_set_float(settings, settings->floats.video_scale, (float)window_scale);

   if (!settings->bools.video_fullscreen)
      command_event(CMD_EVENT_REINIT, NULL);

   rarch_ctl(RARCH_CTL_SET_WINDOWED_SCALE, &idx);

   return true;
}