#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_14__ {TYPE_3__* format; TYPE_2__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;
struct TYPE_16__ {int stream_type; } ;
struct TYPE_15__ {char* name; int /*<<< orphan*/  value; } ;
struct TYPE_13__ {int extradata_size; } ;
struct TYPE_12__ {int /*<<< orphan*/ * extradata; TYPE_1__* module; } ;
struct TYPE_11__ {scalar_t__ extra; } ;
typedef  TYPE_5__ PARAMETER_T ;
typedef  TYPE_6__ MP4_PAYLOAD_T ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
#define  MPEG4_AUDIO_STREAM 128 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  hex_to_byte_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp4_decode_audio_config (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ vc_container_track_allocate_extradata (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  vc_containers_list_find_entry (int /*<<< orphan*/  const*,TYPE_5__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_get_config(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track,
      const VC_CONTAINERS_LIST_T *params)
{
   MP4_PAYLOAD_T *extra = (MP4_PAYLOAD_T *)track->priv->module->extra;
   PARAMETER_T param;
   uint32_t config_len;
   VC_CONTAINER_STATUS_T status;
   uint8_t *config;
   VC_CONTAINER_BITS_T bit_stream;

   param.name = "config";
   if (!vc_containers_list_find_entry(params, &param) || !param.value)
   {
      LOG_ERROR(p_ctx, "MPEG-4: config parameter missing");
      return VC_CONTAINER_ERROR_FORMAT_INVALID;
   }

   config_len = strlen(param.value);
   if (config_len & 1)
   {
      LOG_ERROR(p_ctx, "MPEG-4: config parameter invalid");
      return VC_CONTAINER_ERROR_FORMAT_INVALID;
   }
   config_len /= 2;

   /* Copy AudioSpecificConfig into track extradata, to be decoded by client */
   status = vc_container_track_allocate_extradata(p_ctx, track, config_len);
   if(status != VC_CONTAINER_SUCCESS) return status;

   config = track->priv->extradata;
   track->format->extradata_size = config_len;
   hex_to_byte_buffer(param.value, config, config_len);

   /* Decode config locally, to determine sample rate, etc. */
   BITS_INIT(p_ctx, &bit_stream, config, config_len);

   switch (extra->stream_type)
   {
   case MPEG4_AUDIO_STREAM:
      if (!mp4_decode_audio_config(p_ctx, track, &bit_stream))
         return VC_CONTAINER_ERROR_FORMAT_INVALID;
      break;
   default:
      /* Other stream types not yet supported */
      LOG_ERROR(p_ctx, "MPEG-4: stream type %d not supported", extra->stream_type);
      return VC_CONTAINER_ERROR_FORMAT_INVALID;
   }

   return VC_CONTAINER_SUCCESS;
}