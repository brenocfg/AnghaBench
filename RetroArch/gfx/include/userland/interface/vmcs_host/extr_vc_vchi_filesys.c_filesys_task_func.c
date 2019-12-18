#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {scalar_t__ initialised; int /*<<< orphan*/  open_handle; int /*<<< orphan*/  vc_msg; int /*<<< orphan*/  filesys_msg_avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCHI_FLAGS_NONE ; 
 scalar_t__ VCOS_SUCCESS ; 
 TYPE_1__ vc_filesys_client ; 
 scalar_t__ vc_fs_message_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_hostfs_init () ; 
 scalar_t__ vchi_msg_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchi_service_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchi_service_use (int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_event_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *filesys_task_func(void *arg)
{
   int32_t success;
   uint32_t msg_len;

   (void)arg;

   vc_hostfs_init();

   while(1) {
      // wait for the semaphore to say that there is a message
      if (vcos_event_wait(&vc_filesys_client.filesys_msg_avail) != VCOS_SUCCESS || vc_filesys_client.initialised == 0)
         break;

      vchi_service_use(vc_filesys_client.open_handle);
      // read the message - should we really "peek" this
      while (1) {
         success = vchi_msg_dequeue(vc_filesys_client.open_handle, &vc_filesys_client.vc_msg,
                                    sizeof(vc_filesys_client.vc_msg), &msg_len, VCHI_FLAGS_NONE);
         if (!success)
            break;

         /* coverity[tainted_string_argument] */
         success = (int32_t) vc_fs_message_handler(&vc_filesys_client.vc_msg, msg_len);
         (void)success;
      }
      vchi_service_release(vc_filesys_client.open_handle);
   }

   return 0;
}