#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;
struct TYPE_15__ {scalar_t__ size_length; scalar_t__ constant_size; scalar_t__ auxiliary_length; scalar_t__ constant_duration; scalar_t__ object_type; scalar_t__ dts_delta_length; scalar_t__ cts_delta_length; scalar_t__ index_delta_length; scalar_t__ index_length; } ;
struct TYPE_13__ {TYPE_1__* module; } ;
struct TYPE_12__ {int /*<<< orphan*/  payload_handler; TYPE_4__* extra; } ;
typedef  TYPE_4__ MP4_PAYLOAD_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mp4_check_parameters (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ mp4_check_unsupported_features (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ mp4_get_config (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ mp4_get_mode (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ mp4_get_stream_type (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mp4_payload_handler ; 
 int /*<<< orphan*/  rtp_get_parameter_u32 (int /*<<< orphan*/  const*,char*,scalar_t__*) ; 

VC_CONTAINER_STATUS_T mp4_parameter_handler(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track,
      const VC_CONTAINERS_LIST_T *params)
{
   MP4_PAYLOAD_T *extra;
   VC_CONTAINER_STATUS_T status;

   /* See RFC3640, section 4.1, for parameter names and details. */
   extra = (MP4_PAYLOAD_T *)malloc(sizeof(MP4_PAYLOAD_T));
   if (!extra)
      return VC_CONTAINER_ERROR_OUT_OF_MEMORY;
   track->priv->module->extra = extra;
   memset(extra, 0, sizeof(MP4_PAYLOAD_T));

   /* Mandatory parameters */
   status = mp4_get_stream_type(p_ctx, track, params);
   if (status != VC_CONTAINER_SUCCESS) return status;

   status = mp4_get_config(p_ctx, track, params);
   if (status != VC_CONTAINER_SUCCESS) return status;

   status = mp4_get_mode(p_ctx, track, params);
   if (status != VC_CONTAINER_SUCCESS) return status;

   /* Unsupported parameters */
   status = mp4_check_unsupported_features(p_ctx, track, params);
   if (status != VC_CONTAINER_SUCCESS) return status;

   /* Optional parameters */
   rtp_get_parameter_u32(params, "sizeLength", &extra->size_length);
   rtp_get_parameter_u32(params, "indexLength", &extra->index_length);
   rtp_get_parameter_u32(params, "indexDeltaLength", &extra->index_delta_length);
   rtp_get_parameter_u32(params, "CTSDeltaLength", &extra->cts_delta_length);
   rtp_get_parameter_u32(params, "DTSDeltaLength", &extra->dts_delta_length);
   rtp_get_parameter_u32(params, "objectType", &extra->object_type);
   rtp_get_parameter_u32(params, "constantSize", &extra->constant_size);
   rtp_get_parameter_u32(params, "constantDuration", &extra->constant_duration);
   rtp_get_parameter_u32(params, "auxiliaryDataSizeLength", &extra->auxiliary_length);

   if (extra->constant_size && extra->size_length)
   {
      LOG_ERROR(p_ctx, "MPEG4: constantSize and sizeLength cannot both be set.");
      return VC_CONTAINER_ERROR_FORMAT_INVALID;
   }

   status = mp4_check_parameters(p_ctx, track);
   if (status != VC_CONTAINER_SUCCESS) return status;

   track->priv->module->payload_handler = mp4_payload_handler;

   return VC_CONTAINER_SUCCESS;
}