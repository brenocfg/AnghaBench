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
 int Mix_PlayChannel (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 int /*<<< orphan*/  sound ; 

int play() {
  int channel = Mix_PlayChannel(-1, sound, 0);
  assert(channel == 0);

  emscripten_run_script("setTimeout(Module['_play2'], 500)");
  return channel;
}