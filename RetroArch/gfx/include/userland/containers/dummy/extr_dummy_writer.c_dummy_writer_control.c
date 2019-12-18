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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  VC_CONTAINER_TRACK_T ;
struct TYPE_4__ {int tracks_num; int /*<<< orphan*/ ** tracks; } ;
typedef  TYPE_1__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int VC_CONTAINER_CONTROL_T ;

/* Variables and functions */
#define  VC_CONTAINER_CONTROL_TRACK_ADD 129 
#define  VC_CONTAINER_CONTROL_TRACK_ADD_DONE 128 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/ * vc_container_allocate_track (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T dummy_writer_control( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_CONTROL_T operation, va_list args )
{
   VC_CONTAINER_TRACK_T *track;
   VC_CONTAINER_PARAM_UNUSED(args);

   switch(operation)
   {
   case VC_CONTAINER_CONTROL_TRACK_ADD:
      if(p_ctx->tracks_num >= 2) return VC_CONTAINER_ERROR_OUT_OF_RESOURCES;

      /* Allocate and initialise track data */
      p_ctx->tracks[p_ctx->tracks_num] = track = vc_container_allocate_track(p_ctx, 0);
      if(!track) return VC_CONTAINER_ERROR_OUT_OF_MEMORY;

      p_ctx->tracks_num++;
      return VC_CONTAINER_SUCCESS;

   case VC_CONTAINER_CONTROL_TRACK_ADD_DONE:
      return VC_CONTAINER_SUCCESS;

   default: return VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION;
   }
}