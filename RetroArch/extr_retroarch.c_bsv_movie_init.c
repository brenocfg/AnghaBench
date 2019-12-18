#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rewind_granularity; } ;
struct TYPE_7__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_8__ {char* movie_start_path; int movie_playback; scalar_t__ movie_start_recording; scalar_t__ movie_start_playback; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_FAILED_TO_LOAD_MOVIE_FILE ; 
 int /*<<< orphan*/  MSG_FAILED_TO_START_MOVIE_RECORD ; 
 int /*<<< orphan*/  MSG_STARTING_MOVIE_PLAYBACK ; 
 int /*<<< orphan*/  MSG_STARTING_MOVIE_RECORD_TO ; 
 int /*<<< orphan*/  RARCH_ERR (char*,char*,...) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*,...) ; 
 int /*<<< orphan*/  RARCH_MOVIE_PLAYBACK ; 
 int /*<<< orphan*/  RARCH_MOVIE_RECORD ; 
 int /*<<< orphan*/  bsv_movie_init_handle (char*,int /*<<< orphan*/ ) ; 
 TYPE_5__ bsv_movie_state ; 
 int /*<<< orphan*/  configuration_set_uint (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* configuration_settings ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static bool bsv_movie_init(void)
{
   bool set_granularity = false;

   if (bsv_movie_state.movie_start_playback)
   {
      if (!bsv_movie_init_handle(bsv_movie_state.movie_start_path,
                  RARCH_MOVIE_PLAYBACK))
      {
         RARCH_ERR("%s: \"%s\".\n",
               msg_hash_to_str(MSG_FAILED_TO_LOAD_MOVIE_FILE),
               bsv_movie_state.movie_start_path);
         return false;
      }

      bsv_movie_state.movie_playback = true;
      runloop_msg_queue_push(msg_hash_to_str(MSG_STARTING_MOVIE_PLAYBACK),
            2, 180, false,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      RARCH_LOG("%s.\n", msg_hash_to_str(MSG_STARTING_MOVIE_PLAYBACK));

      set_granularity = true;
   }
   else if (bsv_movie_state.movie_start_recording)
   {
      if (!bsv_movie_init_handle(bsv_movie_state.movie_start_path,
                  RARCH_MOVIE_RECORD))
      {
         runloop_msg_queue_push(
               msg_hash_to_str(MSG_FAILED_TO_START_MOVIE_RECORD),
               1, 180, true,
               NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
         RARCH_ERR("%s.\n",
               msg_hash_to_str(MSG_FAILED_TO_START_MOVIE_RECORD));
         return false;
      }

      {
         char msg[8192];
         snprintf(msg, sizeof(msg),
               "%s \"%s\".",
               msg_hash_to_str(MSG_STARTING_MOVIE_RECORD_TO),
               bsv_movie_state.movie_start_path);

         runloop_msg_queue_push(msg, 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
         RARCH_LOG("%s \"%s\".\n",
               msg_hash_to_str(MSG_STARTING_MOVIE_RECORD_TO),
               bsv_movie_state.movie_start_path);
      }

      set_granularity = true;
   }

   if (set_granularity)
   {
      settings_t *settings    = configuration_settings;
      configuration_set_uint(settings,
            settings->uints.rewind_granularity, 1);
   }

   return true;
}