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
struct TYPE_4__ {char* path_softfilter_plugin; } ;
struct TYPE_5__ {TYPE_1__ paths; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_REINIT ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* config_get_ptr () ; 

__attribute__((used)) static int action_start_video_filter_file_load(unsigned type, const char *label)
{
   settings_t *settings = config_get_ptr();

   if (!settings)
      return -1;

   settings->paths.path_softfilter_plugin[0] = '\0';
   command_event(CMD_EVENT_REINIT, NULL);
   return 0;
}