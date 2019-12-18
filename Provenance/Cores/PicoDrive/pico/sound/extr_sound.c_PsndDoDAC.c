#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dacout; } ;

/* Variables and functions */
 int POPT_EN_STEREO ; 
 int PicoOpt ; 
 int PsndDacLine ; 
 short* PsndOut ; 
 int* dac_info ; 
 TYPE_1__ ym2612 ; 

void PsndDoDAC(int line_to)
{
  int pos, pos1, len;
  int dout = ym2612.dacout;
  int line_from = PsndDacLine;

  if (line_to >= 312)
    line_to = 311;

  PsndDacLine = line_to + 1;

  pos =dac_info[line_from]>>4;
  pos1=dac_info[line_to];
  len = ((pos1>>4)-pos) + (pos1&0xf);
  if (!len) return;

  if (PicoOpt & POPT_EN_STEREO) {
    short *d = PsndOut + pos*2;
    for (; len > 0; len--, d+=2) *d = dout;
  } else {
    short *d = PsndOut + pos;
    for (; len > 0; len--, d++)  *d = dout;
  }
}