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
 int MIX_MAX_VOLUME ; 
 int /*<<< orphan*/  Mix_HaltChannel (int) ; 
 int /*<<< orphan*/  Mix_HaltMusic () ; 
 int /*<<< orphan*/  Mix_Pause (int) ; 
 int /*<<< orphan*/  Mix_PauseMusic () ; 
 int Mix_Paused (int) ; 
 int Mix_PausedMusic () ; 
 int Mix_PlayChannel (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Mix_PlayMusic (int /*<<< orphan*/ ,int) ; 
 int Mix_Playing (int) ; 
 int Mix_PlayingMusic () ; 
 int /*<<< orphan*/  Mix_Resume (int) ; 
 int /*<<< orphan*/  Mix_ResumeMusic () ; 
 int /*<<< orphan*/  Mix_Volume (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  music ; 
 int /*<<< orphan*/  noiseLoop ; 
 int noiseLoopChannel ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  sound ; 
 int soundChannel ; 

void one_iter() {
  static int frames = 0;
  frames++;
  
  switch( frames ) {
    case 1:
      soundChannel = Mix_PlayChannel(-1, sound, 0);
      printf("channel = %d", soundChannel);
      assert(soundChannel != -1 && soundChannel != 0);

      noiseLoopChannel = Mix_PlayChannel(-1, noiseLoop, -1);
      printf("noiseLoopChannel = %d", noiseLoopChannel);
      assert(noiseLoopChannel != -1 && noiseLoopChannel != 0);
      // set noiseLoopChannel to half volume
      Mix_Volume(noiseLoopChannel,MIX_MAX_VOLUME/10);
      break;
    case 2:
      printf("channel %d is playing = %d", soundChannel, Mix_Playing(soundChannel));
      assert(Mix_Playing(soundChannel));
      break;
    case 30:
      Mix_Pause(soundChannel);
      Mix_PlayMusic(music, 1);
      break;
    case 31:
      assert(Mix_Paused(soundChannel));
      assert(Mix_PlayingMusic());
      break;
    case 60:
      Mix_Resume(soundChannel);
      Mix_PauseMusic();
      break;
    case 61:
      assert(Mix_Playing(soundChannel));
      assert(Mix_PausedMusic());
      break;
    case 90:
      Mix_ResumeMusic();
      break;
    case 91:
      assert(Mix_PlayingMusic());
      break;
    case 120:
      Mix_HaltChannel(soundChannel);
      Mix_HaltMusic();
#ifdef REPORT_RESULT
      REPORT_RESULT(1);
#endif
      break;
  };
}