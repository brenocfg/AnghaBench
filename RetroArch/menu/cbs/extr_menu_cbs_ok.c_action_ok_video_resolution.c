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
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_OK_DL_DROPDOWN_BOX_LIST_RESOLUTION ; 
 int /*<<< orphan*/  CMD_EVENT_REINIT ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  generic_action_ok_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_action_ok_displaylist_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ video_driver_get_video_output_size (unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  video_driver_set_video_mode (unsigned int,unsigned int,int) ; 

__attribute__((used)) static int action_ok_video_resolution(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
#if defined(__CELLOS_LV2__) || defined(GEKKO)
   unsigned width   = 0;
   unsigned  height = 0;

   if (video_driver_get_video_output_size(&width, &height))
   {
      char msg[PATH_MAX_LENGTH];

      msg[0] = '\0';

#if defined(__CELLOS_LV2__) || defined(_WIN32)
      generic_action_ok_command(CMD_EVENT_REINIT);
#endif
      video_driver_set_video_mode(width, height, true);
#ifdef GEKKO
      if (width == 0 || height == 0)
         strlcpy(msg, "Applying: DEFAULT", sizeof(msg));
      else
#endif
         snprintf(msg, sizeof(msg),
               "Applying: %dx%d\n START to reset",
               width, height);
      runloop_msg_queue_push(msg, 1, 100, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   }
#else
   generic_action_ok_displaylist_push(
         NULL,
         NULL, NULL, 0, idx, 0,
         ACTION_OK_DL_DROPDOWN_BOX_LIST_RESOLUTION);
#endif

   return 0;
}