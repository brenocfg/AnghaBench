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
 int /*<<< orphan*/  Mix_AllocateChannels (int) ; 
 int /*<<< orphan*/  Mix_CloseAudio () ; 
 scalar_t__ Mix_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Mix_LoadWAV (char*) ; 
 int Mix_OpenAudio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Mix_Quit () ; 
 int /*<<< orphan*/  SDL_INIT_AUDIO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int kNumChannels ; 
 int loadAndPlay () ; 
 int /*<<< orphan*/  sound ; 

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_AUDIO);
  Mix_Init(MIX_INIT_OGG);

  int ret = Mix_OpenAudio(0, 0, 0, 0); // we ignore all these..
  assert(ret == 0);

  Mix_AllocateChannels(kNumChannels);

  sound = Mix_LoadWAV("sound.ogg");

  // allocate all the channels
  for ( int i = 0; i < kNumChannels; i++ )
  {
    assert(loadAndPlay() != -1);
  }

    // This point, we should have exhausted our channels




  int lastChannel = loadAndPlay();

#ifdef __EMSCRIPTEN__
  int result = (lastChannel == -1);
  REPORT_RESULT(result);
#endif

  assert(lastChannel == -1);

  // force a quit
  while(Mix_Init(0))
    Mix_Quit();
  Mix_CloseAudio();

  return 0;
}