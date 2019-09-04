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

/* Variables and functions */
 int /*<<< orphan*/  MIX_INIT_OGG ; 
 int /*<<< orphan*/  Mix_CloseAudio () ; 
 scalar_t__ Mix_Init (int /*<<< orphan*/ ) ; 
 int Mix_LoadMUS (char*) ; 
 int Mix_LoadWAV (char*) ; 
 int Mix_OpenAudio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Mix_Quit () ; 
 int /*<<< orphan*/  Mix_ReserveChannels (int) ; 
 int /*<<< orphan*/  SDL_INIT_AUDIO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int music ; 
 int noiseLoop ; 
 int /*<<< orphan*/  one_iter ; 
 int sound ; 

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_AUDIO);
  Mix_Init(MIX_INIT_OGG);
  
  // This reserves channel 0 for other purposes.
  // We are just going to verify that we are not
  // allocated channel 0 when we call Mix_PlayChannel(-1, ...)
  Mix_ReserveChannels(1);
  
  int ret = Mix_OpenAudio(0, 0, 0, 0); // we ignore all these..
  assert(ret == 0);

  sound = Mix_LoadWAV("sound.ogg");
  assert(sound);
  noiseLoop = Mix_LoadWAV("noise.ogg");
  assert(noiseLoop);

  music = Mix_LoadMUS("music.ogg");
  assert(music);
  emscripten_set_main_loop(one_iter, 30, 0);

  // force a quit
  while(Mix_Init(0))
    Mix_Quit();
  Mix_CloseAudio();

  return 0;
}