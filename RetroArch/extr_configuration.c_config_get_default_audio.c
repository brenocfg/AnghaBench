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
typedef  enum audio_driver_enum { ____Placeholder_audio_driver_enum } audio_driver_enum ;

/* Variables and functions */
#define  AUDIO_AL 156 
#define  AUDIO_ALSA 155 
#define  AUDIO_ALSATHREAD 154 
#define  AUDIO_AUDIOIO 153 
#define  AUDIO_COREAUDIO 152 
#define  AUDIO_COREAUDIO3 151 
#define  AUDIO_CTR 150 
 int AUDIO_DEFAULT_DRIVER ; 
#define  AUDIO_DSOUND 149 
#define  AUDIO_EXT 148 
#define  AUDIO_JACK 147 
#define  AUDIO_NULL 146 
#define  AUDIO_OSS 145 
#define  AUDIO_PS2 144 
#define  AUDIO_PS3 143 
#define  AUDIO_PSP 142 
#define  AUDIO_PULSE 141 
#define  AUDIO_ROAR 140 
#define  AUDIO_RSOUND 139 
#define  AUDIO_RWEBAUDIO 138 
#define  AUDIO_SDL 137 
#define  AUDIO_SDL2 136 
#define  AUDIO_SL 135 
#define  AUDIO_SWITCH 134 
#define  AUDIO_TINYALSA 133 
#define  AUDIO_WASAPI 132 
#define  AUDIO_WII 131 
#define  AUDIO_WIIU 130 
#define  AUDIO_XAUDIO 129 
#define  AUDIO_XENON360 128 

const char *config_get_default_audio(void)
{
   enum audio_driver_enum default_driver = AUDIO_DEFAULT_DRIVER;

   switch (default_driver)
   {
      case AUDIO_RSOUND:
         return "rsound";
      case AUDIO_AUDIOIO:
         return "audioio";
      case AUDIO_OSS:
         return "oss";
      case AUDIO_ALSA:
         return "alsa";
      case AUDIO_ALSATHREAD:
         return "alsathread";
      case AUDIO_TINYALSA:
         return "tinyalsa";
      case AUDIO_ROAR:
         return "roar";
      case AUDIO_COREAUDIO:
         return "coreaudio";
      case AUDIO_COREAUDIO3:
         return "coreaudio3";
      case AUDIO_AL:
         return "openal";
      case AUDIO_SL:
         return "opensl";
      case AUDIO_SDL:
         return "sdl";
      case AUDIO_SDL2:
         return "sdl2";
      case AUDIO_DSOUND:
         return "dsound";
      case AUDIO_WASAPI:
         return "wasapi";
      case AUDIO_XAUDIO:
         return "xaudio";
      case AUDIO_PULSE:
         return "pulse";
      case AUDIO_EXT:
         return "ext";
      case AUDIO_XENON360:
         return "xenon360";
      case AUDIO_PS3:
         return "ps3";
      case AUDIO_WII:
         return "gx";
      case AUDIO_WIIU:
         return "AX";
      case AUDIO_PSP:
#if defined(VITA)
         return "vita";
#elif defined(ORBIS)
         return "orbis";
#else
         return "psp";
#endif
      case AUDIO_PS2:
         return "ps2";
      case AUDIO_CTR:
         return "dsp";
      case AUDIO_SWITCH:
#if defined(HAVE_LIBNX)
         return "switch_audren_thread";
#else
         return "switch";
#endif
      case AUDIO_RWEBAUDIO:
         return "rwebaudio";
      case AUDIO_JACK:
         return "jack";
      case AUDIO_NULL:
         break;
   }

   return "null";
}