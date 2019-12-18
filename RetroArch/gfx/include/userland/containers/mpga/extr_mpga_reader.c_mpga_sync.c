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
typedef  char uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_13__ {scalar_t__ (* pf_parse_header ) (char*,scalar_t__*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ;int version; unsigned int layer; unsigned int sample_rate; unsigned int channels; unsigned int frame_size_samples; unsigned int frame_bitrate; scalar_t__ frame_size; scalar_t__ frame_data_left; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_11__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (TYPE_2__*,char*,...) ; 
 int MPGA_HEADER_SIZE ; 
 int MPGA_MAX_BAD_FRAMES ; 
 int PEEK_BYTES (TYPE_2__*,char*,int) ; 
 int PEEK_BYTES_AT (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int SKIP_BYTES (TYPE_2__*,unsigned int) ; 
 scalar_t__ VC_CONTAINER_ERROR_EOS ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mpga_check_frame_header (TYPE_2__*,TYPE_3__*,char*) ; 
 scalar_t__ stub1 (char*,scalar_t__*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mpga_sync( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status;
   uint8_t frame_header[MPGA_HEADER_SIZE];
   uint32_t frame_size;
   unsigned int frame_bitrate, version, layer, sample_rate, channels;
   unsigned int frame_size_samples, offset;
   int sync_count = 0;

   /* If we can't see a full frame header, we treat this as EOS although it
      could be a bad stream as well, the caller should distinct between
      these two cases */
   if (PEEK_BYTES(p_ctx, (uint8_t*)frame_header, MPGA_HEADER_SIZE) != MPGA_HEADER_SIZE)
      return VC_CONTAINER_ERROR_EOS;

   while (sync_count++ < MPGA_MAX_BAD_FRAMES)
   {
      status = module->pf_parse_header(frame_header, &frame_size, &frame_bitrate,
                                       &version, &layer, &sample_rate, &channels,
                                       &frame_size_samples, &offset);
      if (status == VC_CONTAINER_SUCCESS &&
          frame_size /* We do not support free format streams */)
      {
         LOG_DEBUG(p_ctx, "MPEGv%d, layer %d, %d bps, %d Hz",
                   version, layer, frame_bitrate, sample_rate);
         if (PEEK_BYTES_AT(p_ctx, (int64_t)frame_size, frame_header, MPGA_HEADER_SIZE) != MPGA_HEADER_SIZE ||
             mpga_check_frame_header(p_ctx, module, frame_header) == VC_CONTAINER_SUCCESS)
            break;

         /* If we've reached an ID3 tag then the frame is valid as well */
         if((frame_header[0] == 'I' && frame_header[1] == 'D' && frame_header[2] == '3') ||
            (frame_header[0] == 'T' && frame_header[1] == 'A' && frame_header[2] == 'G'))
            break;
      }
      else if (status == VC_CONTAINER_SUCCESS)
      {
         LOG_DEBUG(p_ctx, "free format not supported");
      }

      if (SKIP_BYTES(p_ctx, 1) != 1 || PEEK_BYTES(p_ctx, (uint8_t*)frame_header, MPGA_HEADER_SIZE) != MPGA_HEADER_SIZE)
         return VC_CONTAINER_ERROR_EOS;
   }

   if(sync_count > MPGA_MAX_BAD_FRAMES) /* We didn't find a valid frame */
      return VC_CONTAINER_ERROR_FORMAT_INVALID;

   if (module->version)
   {
      /* FIXME: we don't currently care whether or not the number of channels changes mid-stream */
      if (version != module->version || layer != module->layer)
      {
         LOG_DEBUG(p_ctx, "version or layer not allowed to change mid-stream");
         return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
      }
   }
   else
   {
      module->version = version;
      module->layer = layer;
      module->sample_rate = sample_rate;
      module->channels = channels;
      module->frame_size_samples = frame_size_samples;
   }

   if(offset) SKIP_BYTES(p_ctx, offset);
   module->frame_data_left = module->frame_size = frame_size - offset;
   module->frame_bitrate = frame_bitrate;

   return VC_CONTAINER_SUCCESS;
}