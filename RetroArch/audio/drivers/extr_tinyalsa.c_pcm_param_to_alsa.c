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
typedef  enum pcm_param { ____Placeholder_pcm_param } pcm_param ;

/* Variables and functions */
#define  PCM_PARAM_ACCESS 142 
#define  PCM_PARAM_BUFFER_BYTES 141 
#define  PCM_PARAM_BUFFER_SIZE 140 
#define  PCM_PARAM_BUFFER_TIME 139 
#define  PCM_PARAM_CHANNELS 138 
#define  PCM_PARAM_FORMAT 137 
#define  PCM_PARAM_FRAME_BITS 136 
#define  PCM_PARAM_PERIODS 135 
#define  PCM_PARAM_PERIOD_BYTES 134 
#define  PCM_PARAM_PERIOD_SIZE 133 
#define  PCM_PARAM_PERIOD_TIME 132 
#define  PCM_PARAM_RATE 131 
#define  PCM_PARAM_SAMPLE_BITS 130 
#define  PCM_PARAM_SUBFORMAT 129 
#define  PCM_PARAM_TICK_TIME 128 
 int SNDRV_PCM_HW_PARAM_ACCESS ; 
 int SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int SNDRV_PCM_HW_PARAM_BUFFER_TIME ; 
 int SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int SNDRV_PCM_HW_PARAM_FORMAT ; 
 int SNDRV_PCM_HW_PARAM_FRAME_BITS ; 
 int SNDRV_PCM_HW_PARAM_PERIODS ; 
 int SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int SNDRV_PCM_HW_PARAM_PERIOD_TIME ; 
 int SNDRV_PCM_HW_PARAM_RATE ; 
 int SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 int SNDRV_PCM_HW_PARAM_SUBFORMAT ; 
 int SNDRV_PCM_HW_PARAM_TICK_TIME ; 

__attribute__((used)) static int pcm_param_to_alsa(enum pcm_param param)
{
   switch (param)
   {
      case PCM_PARAM_ACCESS:
         return SNDRV_PCM_HW_PARAM_ACCESS;
      case PCM_PARAM_FORMAT:
         return SNDRV_PCM_HW_PARAM_FORMAT;
      case PCM_PARAM_SUBFORMAT:
         return SNDRV_PCM_HW_PARAM_SUBFORMAT;
      case PCM_PARAM_SAMPLE_BITS:
         return SNDRV_PCM_HW_PARAM_SAMPLE_BITS;
      case PCM_PARAM_FRAME_BITS:
         return SNDRV_PCM_HW_PARAM_FRAME_BITS;
      case PCM_PARAM_CHANNELS:
         return SNDRV_PCM_HW_PARAM_CHANNELS;
      case PCM_PARAM_RATE:
         return SNDRV_PCM_HW_PARAM_RATE;
      case PCM_PARAM_PERIOD_TIME:
         return SNDRV_PCM_HW_PARAM_PERIOD_TIME;
      case PCM_PARAM_PERIOD_SIZE:
         return SNDRV_PCM_HW_PARAM_PERIOD_SIZE;
      case PCM_PARAM_PERIOD_BYTES:
         return SNDRV_PCM_HW_PARAM_PERIOD_BYTES;
      case PCM_PARAM_PERIODS:
         return SNDRV_PCM_HW_PARAM_PERIODS;
      case PCM_PARAM_BUFFER_TIME:
         return SNDRV_PCM_HW_PARAM_BUFFER_TIME;
      case PCM_PARAM_BUFFER_SIZE:
         return SNDRV_PCM_HW_PARAM_BUFFER_SIZE;
      case PCM_PARAM_BUFFER_BYTES:
         return SNDRV_PCM_HW_PARAM_BUFFER_BYTES;
      case PCM_PARAM_TICK_TIME:
         return SNDRV_PCM_HW_PARAM_TICK_TIME;

      default:
         break;
   }

   return -1;
}