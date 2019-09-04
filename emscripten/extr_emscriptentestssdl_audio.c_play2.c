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
 int /*<<< orphan*/  Mix_ChannelFinished (int /*<<< orphan*/ ) ; 
 int Mix_PlayChannel (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Mix_PlayMusic (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  music ; 
 int /*<<< orphan*/  sound2 ; 
 int /*<<< orphan*/  sound3 ; 

int play2() {
  Mix_ChannelFinished(done);

  int channel2 = Mix_PlayChannel(-1, sound2, 0);
  assert(channel2 == 1);
  int channel3 = Mix_PlayChannel(-1, sound3, 0);
  assert(channel3 == 2);
  assert(Mix_PlayMusic(music, 1) == 0);
  return channel2;
}