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
typedef  enum pcm_format { ____Placeholder_pcm_format } pcm_format ;

/* Variables and functions */
#define  PCM_FORMAT_S16_BE 136 
#define  PCM_FORMAT_S16_LE 135 
#define  PCM_FORMAT_S24_3BE 134 
#define  PCM_FORMAT_S24_3LE 133 
#define  PCM_FORMAT_S24_BE 132 
#define  PCM_FORMAT_S24_LE 131 
#define  PCM_FORMAT_S32_BE 130 
#define  PCM_FORMAT_S32_LE 129 
#define  PCM_FORMAT_S8 128 
 unsigned int SNDRV_PCM_FORMAT_S16_BE ; 
 unsigned int SNDRV_PCM_FORMAT_S16_LE ; 
 unsigned int SNDRV_PCM_FORMAT_S24_3BE ; 
 unsigned int SNDRV_PCM_FORMAT_S24_3LE ; 
 unsigned int SNDRV_PCM_FORMAT_S24_BE ; 
 unsigned int SNDRV_PCM_FORMAT_S24_LE ; 
 unsigned int SNDRV_PCM_FORMAT_S32_BE ; 
 unsigned int SNDRV_PCM_FORMAT_S32_LE ; 
 unsigned int SNDRV_PCM_FORMAT_S8 ; 

__attribute__((used)) static unsigned int pcm_format_to_alsa(enum pcm_format format)
{
   switch (format)
   {
      case PCM_FORMAT_S8:
         return SNDRV_PCM_FORMAT_S8;

      default:
      case PCM_FORMAT_S16_LE:
         return SNDRV_PCM_FORMAT_S16_LE;
      case PCM_FORMAT_S16_BE:
         return SNDRV_PCM_FORMAT_S16_BE;

      case PCM_FORMAT_S24_LE:
         return SNDRV_PCM_FORMAT_S24_LE;
      case PCM_FORMAT_S24_BE:
         return SNDRV_PCM_FORMAT_S24_BE;

      case PCM_FORMAT_S24_3LE:
         return SNDRV_PCM_FORMAT_S24_3LE;
      case PCM_FORMAT_S24_3BE:
         return SNDRV_PCM_FORMAT_S24_3BE;

      case PCM_FORMAT_S32_LE:
         return SNDRV_PCM_FORMAT_S32_LE;
      case PCM_FORMAT_S32_BE:
         return SNDRV_PCM_FORMAT_S32_BE;
   }
}