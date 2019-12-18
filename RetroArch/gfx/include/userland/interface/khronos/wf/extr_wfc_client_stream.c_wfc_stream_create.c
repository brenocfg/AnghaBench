#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_9__ {void* flags; } ;
struct TYPE_10__ {scalar_t__ handle; TYPE_1__ info; int /*<<< orphan*/  registrations; } ;
typedef  TYPE_2__ WFC_STREAM_T ;
struct TYPE_11__ {int size; void* flags; } ;
typedef  TYPE_3__ WFC_STREAM_INFO_T ;
typedef  scalar_t__ WFCNativeStreamType ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_UNLOCK (TYPE_2__*) ; 
 void* VCOS_EEXIST ; 
 void* VCOS_ENOMEM ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ WFC_INVALID_HANDLE ; 
 int WFC_STREAM_RETRIES ; 
 int /*<<< orphan*/  WFC_STREAM_RETRY_DELAY_MS ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vcos_log_info (char*,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int vcos_process_id_current () ; 
 int /*<<< orphan*/  vcos_sleep (int /*<<< orphan*/ ) ; 
 scalar_t__ wfc_server_stream_create_info (scalar_t__,TYPE_3__*,void*,void*) ; 
 TYPE_2__* wfc_stream_create_stream_ptr (scalar_t__,int) ; 
 int /*<<< orphan*/  wfc_stream_destroy_if_ready (TYPE_2__*) ; 

uint32_t wfc_stream_create(WFCNativeStreamType stream, uint32_t flags)
// Create a stream, using the given stream handle (typically assigned by the
// window manager). Return zero if OK.
{
   WFC_STREAM_T *stream_ptr;
   uint32_t result = 0;

   vcos_log_info("%s: stream 0x%x flags 0x%x", VCOS_FUNCTION, stream, flags);

   // Create stream
   stream_ptr = wfc_stream_create_stream_ptr(stream, false);
   if(stream_ptr == NULL)
   {
      vcos_log_error("%s: unable to create data block for stream 0x%x", VCOS_FUNCTION, stream);
      return VCOS_ENOMEM;
   }

   uint64_t pid = vcos_process_id_current();
   uint32_t pid_lo = (uint32_t) pid;
   uint32_t pid_hi = (uint32_t) (pid >> 32);
   int stream_in_use_retries = WFC_STREAM_RETRIES;
   WFC_STREAM_INFO_T info;

   memset(&info, 0, sizeof(info));
   info.size = sizeof(info);
   info.flags = flags;

   do
   {
      stream_ptr->handle = wfc_server_stream_create_info(stream, &info, pid_lo, pid_hi);
      vcos_log_trace("%s: server create returned 0x%x", VCOS_FUNCTION, stream_ptr->handle);

      // If a handle is re-used rapidly, it may still be in use in the server temporarily
      // Retry after a short delay
      if (stream_ptr->handle == WFC_INVALID_HANDLE)
         vcos_sleep(WFC_STREAM_RETRY_DELAY_MS);
   }
   while (stream_ptr->handle == WFC_INVALID_HANDLE && stream_in_use_retries-- > 0);

   if (stream_ptr->handle == WFC_INVALID_HANDLE)
   {
      // Even after the retries, stream handle was still in use. Fail.
      vcos_log_error("%s: stream 0x%x already exists in server", VCOS_FUNCTION, stream);
      result = VCOS_EEXIST;
      wfc_stream_destroy_if_ready(stream_ptr);
   }
   else
   {
      vcos_assert(stream_ptr->handle == stream);

      stream_ptr->registrations++;
      stream_ptr->info.flags = flags;
      STREAM_UNLOCK(stream_ptr);
   }

   return result;
}