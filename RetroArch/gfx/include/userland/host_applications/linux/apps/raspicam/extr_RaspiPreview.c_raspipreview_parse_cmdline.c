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
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {int wantPreview; int wantFullScreenPreview; int opacity; TYPE_1__ previewWindow; } ;
typedef  TYPE_2__ RASPIPREVIEW_PARAMETERS ;

/* Variables and functions */
#define  CommandDisablePreview 131 
#define  CommandFullScreen 130 
#define  CommandOpacity 129 
#define  CommandPreview 128 
 int /*<<< orphan*/  cmdline_commands ; 
 int /*<<< orphan*/  cmdline_commands_size ; 
 int raspicli_get_command_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int*) ; 
 int sscanf (char const*,char*,int*,...) ; 

int raspipreview_parse_cmdline(RASPIPREVIEW_PARAMETERS *params, const char *arg1, const char *arg2)
{
   int command_id, used = 0, num_parameters;

   if (!arg1)
      return 0;

   command_id = raspicli_get_command_id(cmdline_commands, cmdline_commands_size, arg1, &num_parameters);

   // If invalid command, or we are missing a parameter, drop out
   if (command_id==-1 || (command_id != -1 && num_parameters > 0 && arg2 == NULL))
      return 0;

   switch (command_id)
   {
   case CommandPreview: // Preview window
   {
      int tmp;

      params->wantPreview = 1;

      tmp = sscanf(arg2, "%d,%d,%d,%d",
                   &params->previewWindow.x, &params->previewWindow.y,
                   &params->previewWindow.width, &params->previewWindow.height);

      // Failed to get any window parameters, so revert to full screen
      if (tmp == 0)
         params->wantFullScreenPreview = 1;
      else
         params->wantFullScreenPreview = 0;

      used = 2;

      break;
   }

   case CommandFullScreen: // Want full screen preview mode (overrides display rect)
      params->wantPreview = 1;
      params->wantFullScreenPreview = 1;

      used = 1;
      break;

   case CommandOpacity: // Define preview window opacity
      if (sscanf(arg2, "%u", &params->opacity) != 1)
         params->opacity = 255;
      else
         used = 2;
      break;

   case CommandDisablePreview: // Turn off preview output
      params->wantPreview = 0;
      used = 1;
      break;
   }

   return used;
}