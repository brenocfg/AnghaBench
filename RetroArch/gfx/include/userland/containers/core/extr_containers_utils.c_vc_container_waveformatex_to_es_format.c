#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_7__ {int bitrate; int /*<<< orphan*/  codec; int /*<<< orphan*/  es_type; TYPE_2__* type; } ;
typedef  TYPE_3__ VC_CONTAINER_ES_FORMAT_T ;
struct TYPE_5__ {int channels; int sample_rate; int block_align; int bits_per_sample; } ;
struct TYPE_6__ {TYPE_1__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_CODEC_PCM_UNSIGNED_LE ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  VC_CONTAINER_ES_TYPE_AUDIO ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int WAVE_FORMAT_MPEGLAYER3 ; 
 int WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  waveformat_to_codec (int) ; 

VC_CONTAINER_STATUS_T vc_container_waveformatex_to_es_format(uint8_t *p,
   unsigned int buffer_size, unsigned int *extra_offset, unsigned int *extra_size,
   VC_CONTAINER_ES_FORMAT_T *format)
{
   VC_CONTAINER_FOURCC_T fourcc;
   uint32_t waveformat_id;

   if(!p || buffer_size < 16) return VC_CONTAINER_ERROR_INVALID_ARGUMENT;
   waveformat_id = (p[1] << 8) | p[0];
   fourcc = waveformat_to_codec(waveformat_id);

   /* Read the waveformatex header */
   if(extra_offset) *extra_offset = 16;
   if(extra_size) *extra_size = 0;
   format->type->audio.channels = p[2];
   format->type->audio.sample_rate = (p[7] << 24) | (p[6] << 16) | (p[5] << 8) | p[4];
   format->bitrate = ((p[11] << 24) | (p[10] << 16) | (p[9] << 8) | p[8]) * 8;
   format->type->audio.block_align = (p[13] << 8) | p[12];
   format->type->audio.bits_per_sample = (p[15] << 8) | p[14];

   if(waveformat_id == WAVE_FORMAT_PCM && format->type->audio.bits_per_sample == 8)
      fourcc = VC_CONTAINER_CODEC_PCM_UNSIGNED_LE;

   if(buffer_size >= 18)
   {
      if(extra_size)
      {
         *extra_size = (p[17] << 8) | p[16];
         if(*extra_size + 18 > buffer_size) *extra_size = buffer_size - 18;
      }
      if(extra_offset) *extra_offset = 18;
   }

   /* Skip the MPEGLAYER3WAVEFORMAT structure */
   if(waveformat_id == WAVE_FORMAT_MPEGLAYER3 && extra_size)
   {
      if(extra_offset) *extra_offset += *extra_size;
      *extra_size = 0;
   }

   format->es_type = VC_CONTAINER_ES_TYPE_AUDIO;
   format->codec = fourcc;

   return VC_CONTAINER_SUCCESS;
}