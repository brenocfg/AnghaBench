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
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {scalar_t__ bulk_buffer; int /*<<< orphan*/  filesys_lock; int /*<<< orphan*/  response_event; int /*<<< orphan*/  filesys_msg_avail; int /*<<< orphan*/  filesys_thread; scalar_t__ initialised; int /*<<< orphan*/  open_handle; } ;

/* Variables and functions */
 scalar_t__ lock_obtain () ; 
 TYPE_1__ vc_filesys_client ; 
 scalar_t__ vchi_service_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_event_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_free (scalar_t__) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_join (int /*<<< orphan*/ *,void**) ; 

void vc_filesys_stop ()
{
   int32_t result;
   void *dummy;

   if(lock_obtain() != 0)
      return;

   result = vchi_service_close(vc_filesys_client.open_handle);
   vcos_assert(result == 0);

   vc_filesys_client.initialised = 0;

   vcos_event_signal(&vc_filesys_client.filesys_msg_avail);
   vcos_thread_join(&vc_filesys_client.filesys_thread, &dummy);

   vcos_event_delete(&vc_filesys_client.filesys_msg_avail);
   vcos_event_delete(&vc_filesys_client.response_event);
   vcos_mutex_delete(&vc_filesys_client.filesys_lock);

   if(vc_filesys_client.bulk_buffer)
      vcos_free(vc_filesys_client.bulk_buffer);
}