#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rect_req_thread_data; TYPE_2__ info; TYPE_4__* next; TYPE_1__* prev; scalar_t__ to_be_deleted; } ;
typedef  TYPE_3__ WFC_STREAM_T ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;
struct TYPE_12__ {TYPE_1__* prev; } ;
struct TYPE_9__ {TYPE_4__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_UNLOCK () ; 
 int /*<<< orphan*/  STREAM_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  STREAM_UNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int WFC_STREAM_FLAGS_REQ_RECT ; 
 int /*<<< orphan*/  vcos_blockpool_free (TYPE_3__*) ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wfc_server_disconnect () ; 
 TYPE_3__* wfc_stream_global_lock_and_find_stream_ptr (int /*<<< orphan*/ ) ; 
 TYPE_4__* wfc_stream_head ; 

__attribute__((used)) static void wfc_stream_destroy_stream_ptr(WFCNativeStreamType stream)
{
   WFC_STREAM_T *stream_ptr = wfc_stream_global_lock_and_find_stream_ptr(stream);

   vcos_log_trace("%s: stream handle 0x%x", VCOS_FUNCTION, stream);

   if (stream_ptr)
   {
      if (stream_ptr->to_be_deleted)
      {
         STREAM_LOCK(stream_ptr);

         vcos_log_trace("%s: unlinking from list", VCOS_FUNCTION);

         if (stream_ptr->next)
            stream_ptr->next->prev = stream_ptr->prev;
         if (stream_ptr->prev)
            stream_ptr->prev->next = stream_ptr->next;
         else
            wfc_stream_head = stream_ptr->next;

         // No streams left in this process, disconnect
         if (wfc_stream_head == NULL)
            wfc_server_disconnect();
      }
      else
      {
         vcos_log_trace("%s: stream 0x%x recycled before destruction", VCOS_FUNCTION, stream);
         stream_ptr = NULL;
      }
   }
   else
   {
      vcos_log_error("%s: stream 0x%x not found", VCOS_FUNCTION, stream);
   }

   GLOBAL_UNLOCK();

   if (stream_ptr)
   {
      // Stream data block no longer in list, can safely destroy it
      STREAM_UNLOCK(stream_ptr);

      // Wait for rectangle request thread to complete
      if(stream_ptr->info.flags & WFC_STREAM_FLAGS_REQ_RECT)
         vcos_thread_join(&stream_ptr->rect_req_thread_data, NULL);

      // Destroy mutex
      vcos_mutex_delete(&stream_ptr->mutex);

      // Delete
      vcos_blockpool_free(stream_ptr);
   }
}