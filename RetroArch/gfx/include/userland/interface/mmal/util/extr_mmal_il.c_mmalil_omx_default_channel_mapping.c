#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  default_mapping ;
struct TYPE_6__ {int /*<<< orphan*/  member_7; int /*<<< orphan*/  const member_6; int /*<<< orphan*/  const member_5; int /*<<< orphan*/  const member_4; int /*<<< orphan*/  const member_3; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  const member_1; int /*<<< orphan*/  const member_0; } ;
typedef  TYPE_1__ OMX_AUDIO_CHANNELTYPE ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;

/* Variables and functions */
 unsigned int MMAL_COUNTOF (TYPE_1__ const**) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
#define  OMX_AUDIO_ChannelCF 137 
#define  OMX_AUDIO_ChannelCS 136 
#define  OMX_AUDIO_ChannelLF 135 
#define  OMX_AUDIO_ChannelLFE 134 
#define  OMX_AUDIO_ChannelLR 133 
#define  OMX_AUDIO_ChannelLS 132 
#define  OMX_AUDIO_ChannelNone 131 
#define  OMX_AUDIO_ChannelRF 130 
#define  OMX_AUDIO_ChannelRR 129 
#define  OMX_AUDIO_ChannelRS 128 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

MMAL_STATUS_T mmalil_omx_default_channel_mapping(OMX_AUDIO_CHANNELTYPE *channel_mapping, unsigned int nchannels)
{
   static const OMX_AUDIO_CHANNELTYPE default_mapping[][8] = {
      {OMX_AUDIO_ChannelNone},
      {OMX_AUDIO_ChannelCF},
      {OMX_AUDIO_ChannelLF, OMX_AUDIO_ChannelRF},
      {OMX_AUDIO_ChannelLF, OMX_AUDIO_ChannelRF, OMX_AUDIO_ChannelCF},
      {OMX_AUDIO_ChannelLF, OMX_AUDIO_ChannelRF, OMX_AUDIO_ChannelCF,
         OMX_AUDIO_ChannelCS},
      {OMX_AUDIO_ChannelLF, OMX_AUDIO_ChannelRF, OMX_AUDIO_ChannelCF,
         OMX_AUDIO_ChannelLR, OMX_AUDIO_ChannelRR},
      {OMX_AUDIO_ChannelLF, OMX_AUDIO_ChannelRF, OMX_AUDIO_ChannelCF,
         OMX_AUDIO_ChannelLFE, OMX_AUDIO_ChannelLR, OMX_AUDIO_ChannelRR},
      {OMX_AUDIO_ChannelLF, OMX_AUDIO_ChannelRF, OMX_AUDIO_ChannelCF,
         OMX_AUDIO_ChannelLFE, OMX_AUDIO_ChannelLR, OMX_AUDIO_ChannelRR,
         OMX_AUDIO_ChannelCS},
      {OMX_AUDIO_ChannelLF, OMX_AUDIO_ChannelRF, OMX_AUDIO_ChannelCF,
         OMX_AUDIO_ChannelLFE, OMX_AUDIO_ChannelLR, OMX_AUDIO_ChannelRR,
         OMX_AUDIO_ChannelLS, OMX_AUDIO_ChannelRS}
   };

   if (!nchannels || nchannels >= MMAL_COUNTOF(default_mapping))
      return MMAL_EINVAL;

   memcpy(channel_mapping, default_mapping[nchannels],
      sizeof(default_mapping[0][0]) * nchannels);
   return MMAL_SUCCESS;
}