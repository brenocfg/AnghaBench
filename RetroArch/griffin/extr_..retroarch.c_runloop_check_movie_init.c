#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ state_slot; } ;
struct TYPE_7__ {int /*<<< orphan*/  rewind_granularity; } ;
struct TYPE_9__ {TYPE_2__ ints; TYPE_1__ uints; } ;
typedef  TYPE_3__ settings_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_10__ {char* movie_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_FAILED_TO_START_MOVIE_RECORD ; 
 int /*<<< orphan*/  MSG_STARTING_MOVIE_RECORD_TO ; 
 int /*<<< orphan*/  RARCH_ERR (char*,char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*,char*) ; 
 int /*<<< orphan*/  RARCH_MOVIE_RECORD ; 
 int /*<<< orphan*/  bsv_movie_init_handle (char*,int /*<<< orphan*/ ) ; 
 TYPE_6__ bsv_movie_state ; 
 int /*<<< orphan*/  bsv_movie_state_handle ; 
 int /*<<< orphan*/  configuration_set_uint (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* configuration_settings ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static bool runloop_check_movie_init(void)
{
   char msg[16384], path[8192];
   settings_t *settings       = configuration_settings;

   msg[0] = path[0]           = '\0';

   configuration_set_uint(settings, settings->uints.rewind_granularity, 1);

   if (settings->ints.state_slot > 0)
      snprintf(path, sizeof(path), "%s%d.bsv",
            bsv_movie_state.movie_path,
            settings->ints.state_slot);
   else
   {
      strlcpy(path, bsv_movie_state.movie_path, sizeof(path));
      strlcat(path, ".bsv", sizeof(path));
   }


   snprintf(msg, sizeof(msg), "%s \"%s\".",
         msg_hash_to_str(MSG_STARTING_MOVIE_RECORD_TO),
         path);

   bsv_movie_init_handle(path, RARCH_MOVIE_RECORD);

   if (!bsv_movie_state_handle)
   {
      runloop_msg_queue_push(
            msg_hash_to_str(MSG_FAILED_TO_START_MOVIE_RECORD),
            2, 180, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      RARCH_ERR("%s\n",
            msg_hash_to_str(MSG_FAILED_TO_START_MOVIE_RECORD));
      return false;
   }

   runloop_msg_queue_push(msg, 2, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   RARCH_LOG("%s \"%s\".\n",
         msg_hash_to_str(MSG_STARTING_MOVIE_RECORD_TO),
         path);

   return true;
}