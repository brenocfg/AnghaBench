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
 int POPT_EN_STEREO ; 
 int PicoOpt ; 
 int /*<<< orphan*/  PicoWriteSound (int) ; 
 int /*<<< orphan*/  PsndClear () ; 
 int PsndLen ; 
 int PsndRender (int,int) ; 
 int emustatus ; 

void PsndGetSamples(int y)
{
#if SIMPLE_WRITE_SOUND
  if (y != 224) return;
  PsndRender(0, PsndLen);
  if (PicoWriteSound)
    PicoWriteSound(PsndLen * ((PicoOpt & POPT_EN_STEREO) ? 4 : 2));
  PsndClear();
#else
  static int curr_pos = 0;

  if (y == 224)
  {
    if (emustatus & 2)
         curr_pos += PsndRender(curr_pos, PsndLen-PsndLen/2);
    else curr_pos  = PsndRender(0, PsndLen);
    if (emustatus & 1)
         emustatus |=  2;
    else emustatus &= ~2;
    if (PicoWriteSound)
      PicoWriteSound(curr_pos * ((PicoOpt & POPT_EN_STEREO) ? 4 : 2));
    // clear sound buffer
    PsndClear();
  }
  else if (emustatus & 3) {
    emustatus|= 2;
    emustatus&=~1;
    curr_pos = PsndRender(0, PsndLen/2);
  }
#endif
}