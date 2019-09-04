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
 int Mix_PlayChannel (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pan () ; 
 int /*<<< orphan*/  sound ; 

int play() {
  int channel = Mix_PlayChannel(-1, sound, -1);
  assert(channel == 0);

  pan();

  return channel;
}