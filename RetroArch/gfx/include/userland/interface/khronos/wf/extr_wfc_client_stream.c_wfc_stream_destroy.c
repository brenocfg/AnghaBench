#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ registrations; } ;
typedef  TYPE_1__ WFC_STREAM_T ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wfc_stream_destroy_if_ready (TYPE_1__*) ; 
 TYPE_1__* wfc_stream_find_stream_ptr (int /*<<< orphan*/ ) ; 

void wfc_stream_destroy(WFCNativeStreamType stream)
// Destroy a stream - unless it is still in use, in which case, mark it for
// destruction once all users have finished with it.
{
   vcos_log_info("%s: stream: %X", VCOS_FUNCTION, stream);

   WFC_STREAM_T *stream_ptr = wfc_stream_find_stream_ptr(stream);

   if (stream_ptr)
   {
      /* If stream is still in use (e.g. it's attached to at least one source/mask
       * which is associated with at least one element) then destruction is delayed
       * until it's no longer in use. */
      if (stream_ptr->registrations> 0)
      {
         stream_ptr->registrations--;
         vcos_log_trace("%s: stream: %X ready to destroy?", VCOS_FUNCTION, stream);
      }
      else
      {
         vcos_log_error("%s: stream: %X destroyed when unregistered", VCOS_FUNCTION, stream);
      }

      // Stream is unlocked by destroy_if_ready
      wfc_stream_destroy_if_ready(stream_ptr);
   }
   else
   {
      vcos_log_warn("%s: stream %X doesn't exist", VCOS_FUNCTION, stream);
   }

}