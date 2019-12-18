#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_16__ {TYPE_4__* priv; TYPE_6__* format; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  const VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_17__ {scalar_t__ codec; TYPE_2__* type; int /*<<< orphan*/  es_type; } ;
typedef  TYPE_6__ VC_CONTAINER_ES_FORMAT_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;
struct TYPE_18__ {scalar_t__ codec; int channels; int /*<<< orphan*/  (* param_handler ) (int /*<<< orphan*/  const*,TYPE_5__*,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  payload_handler; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_15__ {TYPE_3__* module; } ;
struct TYPE_14__ {int /*<<< orphan*/  payload_handler; int /*<<< orphan*/  timestamp_clock; } ;
struct TYPE_12__ {int channels; int block_align; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  bits_per_sample; } ;
struct TYPE_13__ {TYPE_1__ audio; } ;
typedef  TYPE_7__ AUDIO_PAYLOAD_TYPE_DATA_T ;

/* Variables and functions */
 int BITS_TO_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ UNSUPPORTED_CODEC ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_ES_TYPE_AUDIO ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 size_t countof (TYPE_7__*) ; 
 TYPE_7__* static_audio_payload_types ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,TYPE_5__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T decode_static_audio_type(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track,
      const VC_CONTAINERS_LIST_T *param_list,
      uint32_t payload_type)
{
   VC_CONTAINER_ES_FORMAT_T *format = track->format;
   AUDIO_PAYLOAD_TYPE_DATA_T *data = &static_audio_payload_types[payload_type];

   VC_CONTAINER_PARAM_UNUSED(p_ctx);
   VC_CONTAINER_PARAM_UNUSED(param_list);

   vc_container_assert(payload_type < countof(static_audio_payload_types));

   if (data->codec == UNSUPPORTED_CODEC)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   format->es_type = VC_CONTAINER_ES_TYPE_AUDIO;
   format->codec = data->codec;
   format->type->audio.channels = data->channels;
   format->type->audio.sample_rate = data->sample_rate;
   format->type->audio.bits_per_sample = data->bits_per_sample;
   format->type->audio.block_align = data->channels * BITS_TO_BYTES(data->bits_per_sample);
   track->priv->module->timestamp_clock = format->type->audio.sample_rate;
   track->priv->module->payload_handler = data->payload_handler;

   if (data->param_handler)
      data->param_handler(p_ctx, track, param_list);

   return VC_CONTAINER_SUCCESS;
}