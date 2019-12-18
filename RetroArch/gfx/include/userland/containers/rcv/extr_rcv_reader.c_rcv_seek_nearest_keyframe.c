#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  long long int64_t ;
struct TYPE_12__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_14__ {long long timestamp; scalar_t__ framesize; scalar_t__ keyframe; } ;
struct TYPE_13__ {int frame_read; TYPE_5__ frame; scalar_t__ index; scalar_t__ mid_frame; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_11__ {TYPE_3__* module; } ;
typedef  int /*<<< orphan*/  RCV_FRAME_HEADER_T ;
typedef  int /*<<< orphan*/  RCV_FILE_HEADER_T ;

/* Variables and functions */
 int PEEK_BYTES (TYPE_2__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  SEEK (TYPE_2__*,long long) ; 
 int /*<<< orphan*/  SKIP_BYTES (TYPE_2__*,scalar_t__) ; 
 int STREAM_POSITION (TYPE_2__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vc_container_index_add (scalar_t__,long long,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rcv_seek_nearest_keyframe(VC_CONTAINER_T *p_ctx, int64_t *timestamp, int later)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   int64_t prev_keyframe_offset = sizeof(RCV_FILE_HEADER_T); /* set to very first frame */
   int64_t prev_keyframe_timestamp = 0;
   int use_prev_keyframe = !later;

   if(use_prev_keyframe || (module->frame.timestamp * 1000LL > *timestamp))
   {
      /* A seek has been requested to an earlier keyframe, so rewind to the beginning
       * of the stream since there's no information available on previous frames */
      SEEK(p_ctx, sizeof(RCV_FILE_HEADER_T));
      memset(&module->frame, 0, sizeof(RCV_FRAME_HEADER_T));
      module->mid_frame = 0;
      module->frame_read = 0;
   }

   if(module->mid_frame)
   {
      /* Seek back to the start of the current frame */
      SEEK(p_ctx, STREAM_POSITION(p_ctx) - module->frame_read - sizeof(RCV_FILE_HEADER_T));
      module->mid_frame = 0;
      module->frame_read = 0;
   }

   while(1)
   {
      if(PEEK_BYTES(p_ctx, &module->frame, sizeof(RCV_FRAME_HEADER_T)) != sizeof(RCV_FRAME_HEADER_T))
      {
         status = VC_CONTAINER_ERROR_EOS;
         break;
      }

      if(module->frame.keyframe)
      {
         if(module->index)
            vc_container_index_add(module->index, module->frame.timestamp * 1000LL, STREAM_POSITION(p_ctx));

         if((module->frame.timestamp * 1000LL) >= *timestamp)
         {
            if((module->frame.timestamp * 1000LL) == *timestamp)
               use_prev_keyframe = 0;

            *timestamp = module->frame.timestamp * 1000LL;

            break;
         }

         prev_keyframe_offset = STREAM_POSITION(p_ctx);
         prev_keyframe_timestamp = module->frame.timestamp * 1000LL;
      }

      SKIP_BYTES(p_ctx, module->frame.framesize + sizeof(RCV_FRAME_HEADER_T));
   }

   if(use_prev_keyframe)
   {
      *timestamp = prev_keyframe_timestamp;
      status = SEEK(p_ctx, prev_keyframe_offset);
   }

   return status;
}