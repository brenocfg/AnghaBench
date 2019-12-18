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
 int POPT_EN_PSG ; 
 int POPT_EN_STEREO ; 
 int PicoOpt ; 
 int /*<<< orphan*/  PicoWriteSound (int) ; 
 int /*<<< orphan*/  PsndClear () ; 
 int PsndLen ; 
 scalar_t__ PsndLen_exc_add ; 
 int PsndLen_exc_cnt ; 
 scalar_t__ PsndOut ; 
 int /*<<< orphan*/  SN76496Update (scalar_t__,int,int) ; 

void PsndGetSamplesMS(void)
{
  int stereo = (PicoOpt & 8) >> 3;
  int length = PsndLen;

#if !SIMPLE_WRITE_SOUND
  // compensate for float part of PsndLen
  PsndLen_exc_cnt += PsndLen_exc_add;
  if (PsndLen_exc_cnt >= 0x10000) {
    PsndLen_exc_cnt -= 0x10000;
    length++;
  }
#endif

  // PSG
  if (PicoOpt & POPT_EN_PSG)
    SN76496Update(PsndOut, length, stereo);

  // upmix to "stereo" if needed
  if (stereo) {
    int i, *p;
    for (i = length, p = (void *)PsndOut; i > 0; i--, p++)
      *p |= *p << 16;
  }

  if (PicoWriteSound != NULL)
    PicoWriteSound(length * ((PicoOpt & POPT_EN_STEREO) ? 4 : 2));
  PsndClear();
}