#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_7__ {int /*<<< orphan*/  info; int /*<<< orphan*/  registrations; } ;
typedef  TYPE_1__ WFC_STREAM_T ;
struct TYPE_8__ {int size; } ;
typedef  TYPE_2__ WFC_STREAM_INFO_T ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int vcos_process_id_current () ; 
 scalar_t__ wfc_server_connect () ; 
 scalar_t__ wfc_server_stream_get_info (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  wfc_server_stream_register (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_1__* wfc_stream_create_stream_ptr (int /*<<< orphan*/ ,int) ; 

void wfc_stream_register(WFCNativeStreamType stream) {
   uint64_t pid = vcos_process_id_current();
   uint32_t pid_lo = (uint32_t)pid;
   uint32_t pid_hi = (uint32_t)(pid >> 32);

   if (wfc_server_connect() == VCOS_SUCCESS)
   {
      WFC_STREAM_INFO_T info;
      uint32_t status;

      info.size = sizeof(info);
      status = wfc_server_stream_get_info(stream, &info);

      if (status == VCOS_SUCCESS)
      {
         WFC_STREAM_T *stream_ptr = wfc_stream_create_stream_ptr(stream, true);

         if (stream_ptr)
         {
            stream_ptr->registrations++;
            memcpy(&stream_ptr->info, &info, info.size);
            STREAM_UNLOCK(stream_ptr);
         }

         wfc_server_stream_register(stream, pid_lo, pid_hi);
      }
      else
      {
         vcos_log_error("%s: get stream info failed: %u", VCOS_FUNCTION, status);
      }
   }
}