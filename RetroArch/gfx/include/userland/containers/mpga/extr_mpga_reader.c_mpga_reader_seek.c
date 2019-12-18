#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int int64_t ;
struct TYPE_12__ {int duration; TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  scalar_t__ VC_CONTAINER_SEEK_MODE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_SEEK_FLAGS_T ;
struct TYPE_13__ {int sample_rate; int num_frames; int frame_size_samples; int* xing_toc; void* data_offset; int data_size; int frame_index; int frame_time_pos; void* frame_offset; scalar_t__ xing_toc_valid; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_11__ {TYPE_3__* module; } ;

/* Variables and functions */
 int INT64_C (int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  SEEK (TYPE_2__*,void*) ; 
 void* STREAM_POSITION (TYPE_2__*) ; 
 int /*<<< orphan*/  STREAM_SEEKABLE (TYPE_2__*) ; 
 scalar_t__ STREAM_STATUS (TYPE_2__*) ; 
 scalar_t__ VC_CONTAINER_ERROR_EOS ; 
 scalar_t__ VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ ) ; 
 scalar_t__ VC_CONTAINER_SEEK_MODE_TIME ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int mpga_calculate_frame_time (TYPE_2__*) ; 
 scalar_t__ mpga_sync (TYPE_2__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mpga_reader_seek( VC_CONTAINER_T *p_ctx,
                                               int64_t *p_offset,
                                               VC_CONTAINER_SEEK_MODE_T mode,
                                               VC_CONTAINER_SEEK_FLAGS_T flags)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   uint64_t seekpos, position = STREAM_POSITION(p_ctx);
   VC_CONTAINER_PARAM_UNUSED(flags);

   if (mode != VC_CONTAINER_SEEK_MODE_TIME || !STREAM_SEEKABLE(p_ctx))
      return VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION;

   if (*p_offset != INT64_C(0))
   {
      if (!p_ctx->duration)
         return VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION;

      if (module->xing_toc_valid)
      {
         int64_t ppm;
         int percent, lower, upper, delta;

         ppm = (*p_offset * module->sample_rate) / (module->num_frames * module->frame_size_samples);
         ppm = MIN(ppm, INT64_C(999999));

         percent = ppm / 10000;
         delta   = ppm % 10000;

         lower = module->xing_toc[percent];
         upper = percent < 99 ? module->xing_toc[percent + 1] : 256;

         seekpos = module->data_offset +
            (((module->data_size * lower) + (module->data_size * (upper - lower) * delta) / 10000) >> 8);
      }
      else
      {
         /* The following will be accurate for CBR only */
         seekpos = module->data_offset + (*p_offset * module->data_size) / p_ctx->duration;
      }
   }
   else
   {
      seekpos = module->data_offset;
   }

   SEEK(p_ctx, seekpos);
   status = mpga_sync(p_ctx);
   if (status && status != VC_CONTAINER_ERROR_EOS)
      goto error;

   module->frame_index = (*p_offset * module->num_frames + (p_ctx->duration >> 1)) / p_ctx->duration;
   module->frame_offset = STREAM_POSITION(p_ctx) - module->data_offset;

   *p_offset = module->frame_time_pos = mpga_calculate_frame_time(p_ctx);

   return STREAM_STATUS(p_ctx);

error:
   SEEK(p_ctx, position);
   return status;
}