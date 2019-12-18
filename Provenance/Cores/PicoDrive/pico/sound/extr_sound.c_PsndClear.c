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
 int PsndLen ; 
 scalar_t__ PsndLen_exc_add ; 
 short* PsndOut ; 
 int /*<<< orphan*/  memset32 (int*,int /*<<< orphan*/ ,int) ; 

void PsndClear(void)
{
  int len = PsndLen;
  if (PsndLen_exc_add) len++;
  if (PicoOpt & POPT_EN_STEREO)
    memset32((int *) PsndOut, 0, len); // assume PsndOut to be aligned
  else {
    short *out = PsndOut;
    if ((long)out & 2) { *out++ = 0; len--; }
    memset32((int *) out, 0, len/2);
    if (len & 1) out[len-1] = 0;
  }
}