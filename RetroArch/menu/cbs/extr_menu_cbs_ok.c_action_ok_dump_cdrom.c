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
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_NO_DISC_INSERTED ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  cdrom_drive_has_media (char const) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  task_push_cdrom_dump (char const*) ; 

__attribute__((used)) static int action_ok_dump_cdrom(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   if (string_is_empty(label))
      return -1;
#ifdef HAVE_CDROM
   if (!cdrom_drive_has_media(label[0]))
   {
      RARCH_LOG("[CDROM]: No media is inserted or drive is not ready.\n");

      runloop_msg_queue_push(
            msg_hash_to_str(MSG_NO_DISC_INSERTED),
            1, 100, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

      return -1;
   }

   task_push_cdrom_dump(label);
#endif
   return 0;
}