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
typedef  enum audio_resampler_driver_enum { ____Placeholder_audio_resampler_driver_enum } audio_resampler_driver_enum ;

/* Variables and functions */
 int AUDIO_DEFAULT_RESAMPLER_DRIVER ; 
#define  AUDIO_RESAMPLER_CC 131 
#define  AUDIO_RESAMPLER_NEAREST 130 
#define  AUDIO_RESAMPLER_NULL 129 
#define  AUDIO_RESAMPLER_SINC 128 

const char *config_get_default_audio_resampler(void)
{
   enum audio_resampler_driver_enum default_driver = AUDIO_DEFAULT_RESAMPLER_DRIVER;

   switch (default_driver)
   {
      case AUDIO_RESAMPLER_CC:
         return "cc";
      case AUDIO_RESAMPLER_SINC:
         return "sinc";
      case AUDIO_RESAMPLER_NEAREST:
         return "nearest";
      case AUDIO_RESAMPLER_NULL:
         break;
   }

   return "null";
}