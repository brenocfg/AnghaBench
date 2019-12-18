#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spec ;
struct TYPE_4__ {int freq; int channels; int samples; scalar_t__ userdata; int /*<<< orphan*/  callback; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ SDL_AudioSpec ;
typedef  int /*<<< orphan*/  FCEUGI ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_S16SYS ; 
 int /*<<< orphan*/  Buffer ; 
 scalar_t__ BufferIn ; 
 scalar_t__ BufferRead ; 
 int BufferSize ; 
 scalar_t__ BufferWrite ; 
 int /*<<< orphan*/  FCEUI_Sound (int) ; 
 int /*<<< orphan*/  KillSound () ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_AUDIO ; 
 scalar_t__ SDL_InitSubSystem (int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_OpenAudio (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_PauseAudio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _sound ; 
 int /*<<< orphan*/  fillaudio ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int soundbufsize ; 
 int soundrate ; 

int InitSound(FCEUGI *gi)
{
 SDL_AudioSpec spec;
 if(!_sound) return(0);

 memset(&spec,0,sizeof(spec));
 if(SDL_InitSubSystem(SDL_INIT_AUDIO)<0)
 {
  puts(SDL_GetError());
  KillSound();
  return(0);
 }

 spec.freq = soundrate;
 spec.format = AUDIO_S16SYS;
 spec.channels = 1;
 spec.samples = 256;
 spec.callback = fillaudio;
 spec.userdata = 0;

 BufferSize = soundbufsize * soundrate / 1000;

 BufferSize -= spec.samples * 2;		/* SDL uses at least double-buffering, so
						   multiply by 2. */

 if(BufferSize < spec.samples) BufferSize = spec.samples;

 Buffer = malloc(sizeof(int) * BufferSize);
 BufferRead = BufferWrite = BufferIn = 0;

 //printf("SDL Size: %d, Internal size: %d\n",spec.samples,BufferSize);

 if(SDL_OpenAudio(&spec,0)<0)
 {
  puts(SDL_GetError());
  KillSound();
  return(0);
 }
 SDL_PauseAudio(0);
 FCEUI_Sound(soundrate);
 return(1);
}