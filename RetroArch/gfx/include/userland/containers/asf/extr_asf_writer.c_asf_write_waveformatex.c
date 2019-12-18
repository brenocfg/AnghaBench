#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* format; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  extradata; TYPE_2__* type; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  codec; } ;
struct TYPE_6__ {int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  block_align; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channels; } ;
struct TYPE_7__ {TYPE_1__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  WRITE_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_U16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  codec_to_waveformat (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_write_waveformatex( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_TRACK_T *p_track)
{
   /* Write WAVEFORMATEX structure */
   WRITE_U16(p_ctx, codec_to_waveformat(p_track->format->codec), "Codec ID");
   WRITE_U16(p_ctx, p_track->format->type->audio.channels, "Number of Channels");
   WRITE_U32(p_ctx, p_track->format->type->audio.sample_rate, "Samples per Second");
   WRITE_U32(p_ctx, p_track->format->bitrate, "Average Number of Bytes Per Second");
   WRITE_U16(p_ctx, p_track->format->type->audio.block_align, "Block Alignment");
   WRITE_U16(p_ctx, p_track->format->type->audio.bits_per_sample, "Bits Per Sample");
   WRITE_U16(p_ctx, p_track->format->extradata_size, "Codec Specific Data Size");
   WRITE_BYTES(p_ctx, p_track->format->extradata, p_track->format->extradata_size);

   return VC_CONTAINER_SUCCESS;
}