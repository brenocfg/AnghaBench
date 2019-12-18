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
struct TYPE_2__ {int rhythm; int noise_rng; int status; int /*<<< orphan*/ * P_CH; } ;

/* Variables and functions */
 int /*<<< orphan*/  advance () ; 
 int /*<<< orphan*/  advance_lfo () ; 
 int /*<<< orphan*/  chan_calc (int /*<<< orphan*/ *) ; 
 int* output ; 
 int /*<<< orphan*/  rhythm_calc (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ ym2413 ; 

void YM2413Update(int *buffer, int length)
{
  int i, out;

  for( i=0; i < length ; i++ )
  {
    output[0] = 0;
    output[1] = 0;

    advance_lfo();

    /* FM part */
    chan_calc(&ym2413.P_CH[0]);
    chan_calc(&ym2413.P_CH[1]);
    chan_calc(&ym2413.P_CH[2]);
    chan_calc(&ym2413.P_CH[3]);
    chan_calc(&ym2413.P_CH[4]);
    chan_calc(&ym2413.P_CH[5]);

    if(!(ym2413.rhythm&0x20))
    {
      chan_calc(&ym2413.P_CH[6]);
      chan_calc(&ym2413.P_CH[7]);
      chan_calc(&ym2413.P_CH[8]);
    }
    else    /* Rhythm part */
    {
      rhythm_calc(&ym2413.P_CH[0], (ym2413.noise_rng>>0)&1 );
    }

    /* Melody (MO) & Rythm (RO) outputs mixing & amplification (latched bit controls FM output) */
    out = (output[0] + (output[1] * 2)) * 2 * ym2413.status;

    /* Store to stereo sound buffer */
    *buffer++ = out;
    *buffer++ = out;

    advance();
  }
}