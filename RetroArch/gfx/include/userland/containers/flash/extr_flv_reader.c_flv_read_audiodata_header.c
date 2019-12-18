#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_ADPCM_SWF ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_ALAW ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_MP4A ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_MPGA ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_MULAW ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_NELLYMOSER ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_PCM_SIGNED ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_PCM_SIGNED_LE ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_PCM_UNSIGNED ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_SPEEX ; 
 int _READ_U8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T flv_read_audiodata_header(VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_FOURCC_T *codec, int *p_samplerate, int *p_channels, int *p_bps)
{
   int samplerate, channels, bps;
   uint8_t header = _READ_U8(p_ctx);

   switch((header >> 2) & 0x3)
   {
   case 0: samplerate = 5512; break;
   case 1: samplerate = 11025; break;
   case 2: samplerate = 22050; break;
   default:
   case 3: samplerate = 44100; break;
   }

   channels = 1 << (header & 1);
   bps = 8 << ((header >> 1) & 1);

   switch(header >> 4)
   {
   case 0: *codec = bps == 8 ? VC_CONTAINER_CODEC_PCM_UNSIGNED : VC_CONTAINER_CODEC_PCM_SIGNED; break;
   case 1: *codec = VC_CONTAINER_CODEC_ADPCM_SWF; break;
   case 2: *codec = VC_CONTAINER_CODEC_MPGA; break;
   case 3: *codec = bps == 8 ? VC_CONTAINER_CODEC_PCM_UNSIGNED : VC_CONTAINER_CODEC_PCM_SIGNED_LE; break;
   case 4: *codec = VC_CONTAINER_CODEC_NELLYMOSER; samplerate = 8000; channels = 1; break;
   case 5: *codec = VC_CONTAINER_CODEC_NELLYMOSER; samplerate = 16000; channels = 1; break;
   case 6: *codec = VC_CONTAINER_CODEC_NELLYMOSER; channels = 1; break;
   case 7: *codec = VC_CONTAINER_CODEC_ALAW; break;
   case 8: *codec = VC_CONTAINER_CODEC_MULAW; break;
   case 10: *codec = VC_CONTAINER_CODEC_MP4A; samplerate = 44100; channels = 2; break;
   case 11: *codec = VC_CONTAINER_CODEC_SPEEX; break;
   case 14: *codec = VC_CONTAINER_CODEC_MPGA; samplerate = 8000; break;
   default: *codec = 0; break;
   }

   if(p_samplerate) *p_samplerate = samplerate;
   if(p_channels) *p_channels = channels;
   if(p_bps) *p_bps = bps;

   return STREAM_STATUS(p_ctx);
}