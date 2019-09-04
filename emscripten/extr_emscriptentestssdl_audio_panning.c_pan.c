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
 int Mix_SetPanning (int,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  done () ; 
 int /*<<< orphan*/  printf (char*,float,int,int) ; 
 int sin (int) ; 

void pan() {
  static int frames = 0;
  frames++;

  float x = (sin(frames / 30.f) + 1) / 2;

  int channel = 0;
  int left = x * 255;
  int right = (1 - x) * 255;
  printf("%f %d %d\n", x, left, right);
  int panning = Mix_SetPanning(channel, left, right);
  assert(panning != 0);

  if (frames > 30 * 10)
      done();
}