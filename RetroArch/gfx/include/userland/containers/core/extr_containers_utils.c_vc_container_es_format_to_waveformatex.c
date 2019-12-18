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
typedef  int uint16_t ;
struct TYPE_7__ {scalar_t__ es_type; int extradata_size; int bitrate; int /*<<< orphan*/  extradata; TYPE_2__* type; int /*<<< orphan*/  codec; } ;
typedef  TYPE_3__ VC_CONTAINER_ES_FORMAT_T ;
struct TYPE_5__ {int channels; int sample_rate; int block_align; int bits_per_sample; } ;
struct TYPE_6__ {TYPE_1__ audio; } ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 int WAVE_FORMAT_UNKNOWN ; 
 int codec_to_waveformat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

unsigned int vc_container_es_format_to_waveformatex(VC_CONTAINER_ES_FORMAT_T *format,
                                                    uint8_t *buffer, unsigned int buffer_size)
{
   uint16_t waveformat = codec_to_waveformat(format->codec);

   if(format->es_type != VC_CONTAINER_ES_TYPE_AUDIO ||
      waveformat == WAVE_FORMAT_UNKNOWN) return 0;

   if(!buffer) return format->extradata_size + 18;

   if(buffer_size < format->extradata_size + 18) return 0;

   /* Build a waveformatex header */
   buffer[0] = waveformat;
   buffer[1] = waveformat >> 8;
   buffer[2] = format->type->audio.channels;
   buffer[3] = 0;
   buffer[4] = (format->type->audio.sample_rate >> 0) & 0xFF;
   buffer[5] = (format->type->audio.sample_rate >> 8) & 0xFF;
   buffer[6] = (format->type->audio.sample_rate >> 16) & 0xFF;
   buffer[7] = (format->type->audio.sample_rate >> 24) & 0xFF;
   buffer[8] = (format->bitrate >> 3) & 0xFF;
   buffer[9] = (format->bitrate >> 11) & 0xFF;
   buffer[10] = (format->bitrate >> 19) & 0xFF;
   buffer[11] = (format->bitrate >> 27) & 0xFF;
   buffer[12] = (format->type->audio.block_align >> 0) & 0xFF;
   buffer[13] = (format->type->audio.block_align >> 8) & 0xFF;
   buffer[14] = (format->type->audio.bits_per_sample >> 0) & 0xFF;
   buffer[15] = (format->type->audio.bits_per_sample >> 8) & 0xFF;
   buffer[16] = (format->extradata_size >> 0) & 0xFF;
   buffer[17] = (format->extradata_size >> 8) & 0xFF;
   memcpy(buffer+18, format->extradata, format->extradata_size);
   return format->extradata_size + 18;
}