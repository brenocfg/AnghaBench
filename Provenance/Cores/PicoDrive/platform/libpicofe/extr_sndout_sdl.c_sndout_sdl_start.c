#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int freq; int channels; int samples; int /*<<< orphan*/ * userdata; int /*<<< orphan*/  callback; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ SDL_AudioSpec ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_S16LSB ; 
 char* SDL_GetError () ; 
 int SDL_OpenAudio (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_PauseAudio (int /*<<< orphan*/ ) ; 
 scalar_t__ buf_r ; 
 scalar_t__ buf_w ; 
 int /*<<< orphan*/  callback ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sndout_sdl_stop () ; 
 int started ; 
 int /*<<< orphan*/  stderr ; 

int sndout_sdl_start(int rate, int stereo)
{
	SDL_AudioSpec desired;
	int samples, shift;
	int ret;

	if (started)
		sndout_sdl_stop();

	desired.freq = rate;
	desired.format = AUDIO_S16LSB;
	desired.channels = stereo ? 2 : 1;
	desired.callback = callback;
	desired.userdata = NULL;

	samples = rate >> 6;
	for (shift = 8; (1 << shift) < samples; shift++)
		;
	desired.samples = 1 << shift;

	ret = SDL_OpenAudio(&desired, NULL);
	if (ret != 0) {
		fprintf(stderr, "SDL_OpenAudio: %s\n", SDL_GetError());
		return -1;
	}

	buf_w = buf_r = 0;

	SDL_PauseAudio(0);
	started = 1;

	return 0;
}