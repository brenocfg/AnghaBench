#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ audio_opened; } ;
struct TYPE_18__ {TYPE_1__* priv; } ;
struct TYPE_17__ {int buffer_size_min; TYPE_4__* format; TYPE_7__* component; } ;
struct TYPE_16__ {scalar_t__ format; int channels; int samples; int /*<<< orphan*/  freq; TYPE_6__* userdata; int /*<<< orphan*/  callback; } ;
struct TYPE_15__ {scalar_t__ encoding; TYPE_3__* es; } ;
struct TYPE_13__ {int bits_per_sample; int channels; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_14__ {TYPE_2__ audio; } ;
struct TYPE_12__ {TYPE_8__* module; } ;
typedef  TYPE_5__ SDL_AudioSpec ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_6__ MMAL_PORT_T ;
typedef  TYPE_7__ MMAL_COMPONENT_T ;
typedef  TYPE_8__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 scalar_t__ AUDIO_S16SYS ; 
 int FRAME_LENGTH ; 
 int /*<<< orphan*/  LOG_ERROR (char*,char*,int) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 scalar_t__ MMAL_ENCODING_PCM_FLOAT ; 
 scalar_t__ MMAL_ENCODING_PCM_SIGNED ; 
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 scalar_t__ MMAL_FALSE ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ MMAL_TRUE ; 
 int /*<<< orphan*/  SDL_CloseAudio () ; 
 scalar_t__ SDL_OpenAudio (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sdl_callback ; 

__attribute__((used)) static MMAL_STATUS_T sdl_port_set_format(MMAL_PORT_T *port)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   SDL_AudioSpec desired, obtained;

   if (port->format->encoding != MMAL_ENCODING_PCM_SIGNED &&
       port->format->encoding != MMAL_ENCODING_PCM_FLOAT &&
       port->format->es->audio.bits_per_sample != 16 &&
      port->format->es->audio.bits_per_sample != 32)
   {
      LOG_ERROR("port does not support '%4.4s' at %ibps",
                (char *)&port->format->encoding, port->format->es->audio.bits_per_sample);
      return MMAL_EINVAL;
   }

   if (module->audio_opened)
      SDL_CloseAudio();
   module->audio_opened = MMAL_FALSE;

   desired.freq       = port->format->es->audio.sample_rate;
   desired.format     = AUDIO_S16SYS;
   desired.channels   = port->format->es->audio.channels;
   desired.callback   = sdl_callback;
   desired.userdata   = port;
   desired.samples    = FRAME_LENGTH;

   /* Open the sound device. */
   if (SDL_OpenAudio( &desired, &obtained ) < 0)
       return MMAL_ENOSYS;
   module->audio_opened = MMAL_TRUE;

   /* Now have a look at what we got. */
   if (obtained.format != AUDIO_S16SYS)
      return MMAL_ENOSYS;

   port->format->es->audio.sample_rate = obtained.freq;
   port->format->es->audio.channels = obtained.channels;
   port->buffer_size_min = obtained.samples * port->format->es->audio.channels * 2;

   return MMAL_SUCCESS;
}