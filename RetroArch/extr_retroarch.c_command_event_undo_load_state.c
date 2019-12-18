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

/* Variables and functions */
 int /*<<< orphan*/  MSG_FAILED_TO_UNDO_LOAD_STATE ; 
 int /*<<< orphan*/  MSG_NO_STATE_HAS_BEEN_LOADED_YET ; 
 int /*<<< orphan*/  MSG_UNDID_LOAD_STATE ; 
 int /*<<< orphan*/  RARCH_NETPLAY_CTL_LOAD_SAVESTATE ; 
 scalar_t__ content_undo_load_buf_is_empty () ; 
 int /*<<< orphan*/  content_undo_load_state () ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netplay_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void command_event_undo_load_state(char *s, size_t len)
{

   if (content_undo_load_buf_is_empty())
   {
      strlcpy(s,
         msg_hash_to_str(MSG_NO_STATE_HAS_BEEN_LOADED_YET),
         len);
      return;
   }

   if (!content_undo_load_state())
   {
      snprintf(s, len, "%s \"%s\".",
            msg_hash_to_str(MSG_FAILED_TO_UNDO_LOAD_STATE),
            "RAM");
      return;
   }

#ifdef HAVE_NETWORKING
   netplay_driver_ctl(RARCH_NETPLAY_CTL_LOAD_SAVESTATE, NULL);
#endif

   strlcpy(s,
         msg_hash_to_str(MSG_UNDID_LOAD_STATE), len);
}