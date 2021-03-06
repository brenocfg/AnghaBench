#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* priv; TYPE_4__* format; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_13__ {int sample_rate; int channels; int block_align; int /*<<< orphan*/  bits_per_sample; } ;
typedef  TYPE_6__ VC_CONTAINER_AUDIO_FORMAT_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;
struct TYPE_11__ {TYPE_3__* type; } ;
struct TYPE_10__ {TYPE_6__ audio; } ;
struct TYPE_9__ {TYPE_1__* module; } ;
struct TYPE_8__ {int timestamp_clock; } ;

/* Variables and functions */
 int BITS_TO_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHANNELS_NAME ; 
 int /*<<< orphan*/  RATE_NAME ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 scalar_t__ rtp_get_parameter_u32 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T audio_parameter_handler(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track,
      const VC_CONTAINERS_LIST_T *params)
{
   VC_CONTAINER_AUDIO_FORMAT_T *audio = &track->format->type->audio;

   VC_CONTAINER_PARAM_UNUSED(p_ctx);

   /* See RFC3555. Generic audio parameters that can override static payload
    * type defaults. */
   if (rtp_get_parameter_u32(params, RATE_NAME, &audio->sample_rate))
      track->priv->module->timestamp_clock = audio->sample_rate;
   if (rtp_get_parameter_u32(params, CHANNELS_NAME, &audio->channels))
      audio->block_align = audio->channels * BITS_TO_BYTES(audio->bits_per_sample);

   return VC_CONTAINER_SUCCESS;
}