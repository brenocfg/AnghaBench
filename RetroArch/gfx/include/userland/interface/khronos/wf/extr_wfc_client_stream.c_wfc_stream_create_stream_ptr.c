#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int size; } ;
struct TYPE_10__ {int to_be_deleted; struct TYPE_10__* prev; struct TYPE_10__* next; TYPE_1__ info; int /*<<< orphan*/  handle; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ WFC_STREAM_T ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_UNLOCK () ; 
 int /*<<< orphan*/  STREAM_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 TYPE_2__* vcos_blockpool_calloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_blockpool_free (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vcos_verify (int) ; 
 int /*<<< orphan*/  wfc_server_connect () ; 
 int /*<<< orphan*/  wfc_stream_blockpool ; 
 TYPE_2__* wfc_stream_global_lock_and_find_stream_ptr (int /*<<< orphan*/ ) ; 
 TYPE_2__* wfc_stream_head ; 

__attribute__((used)) static WFC_STREAM_T *wfc_stream_create_stream_ptr(WFCNativeStreamType stream, bool allow_duplicate)
{
   WFC_STREAM_T *stream_ptr = wfc_stream_global_lock_and_find_stream_ptr(stream);

   vcos_log_trace("%s: stream handle 0x%x", VCOS_FUNCTION, stream);

   if (stream_ptr && !stream_ptr->to_be_deleted)
   {
      if (!allow_duplicate)
      {
         vcos_log_error("%s: attempt to create duplicate of stream handle 0x%x", VCOS_FUNCTION, stream);
         // Stream already exists, return NULL
         stream_ptr = NULL;
      }
      else
      {
         vcos_log_trace("%s: duplicate of stream handle 0x%x created", VCOS_FUNCTION, stream);

         STREAM_LOCK(stream_ptr);
      }
   }
   else
   {
      if (stream_ptr)
      {
         vcos_log_trace("%s: recycling data block for stream handle 0x%x", VCOS_FUNCTION, stream);

         // Recycle existing entry
         stream_ptr->to_be_deleted = false;

         STREAM_LOCK(stream_ptr);
      }
      else
      {
         vcos_log_trace("%s: allocating block for stream handle 0x%x", VCOS_FUNCTION, stream);

         // Create new block and insert it into the list
         stream_ptr = vcos_blockpool_calloc(&wfc_stream_blockpool);

         if (stream_ptr)
         {
            VCOS_STATUS_T status;

            status = vcos_mutex_create(&stream_ptr->mutex, "WFC_STREAM_T mutex");
            if (vcos_verify(status == VCOS_SUCCESS))
            {
               STREAM_LOCK(stream_ptr);

               // First stream in this process, connect
               if (!wfc_stream_head)
                  wfc_server_connect();

               stream_ptr->handle = stream;
               stream_ptr->info.size = sizeof(stream_ptr->info);

               // Insert data into list
               stream_ptr->next = wfc_stream_head;
               if (wfc_stream_head)
                  wfc_stream_head->prev = stream_ptr;
               wfc_stream_head = stream_ptr;
            }
            else
            {
               vcos_log_error("%s: unable to create mutex for stream handle 0x%x", VCOS_FUNCTION, stream);
               vcos_blockpool_free(stream_ptr);
               stream_ptr = NULL;
            }
         }
         else
         {
            vcos_log_error("%s: unable to allocate data for stream handle 0x%x", VCOS_FUNCTION, stream);
         }
      }
   }

   GLOBAL_UNLOCK();

   return stream_ptr;
}