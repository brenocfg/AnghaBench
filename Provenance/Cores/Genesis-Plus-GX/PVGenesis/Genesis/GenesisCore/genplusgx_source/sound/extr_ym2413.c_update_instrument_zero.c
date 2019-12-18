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
typedef  int UINT8 ;
typedef  size_t UINT32 ;
struct TYPE_2__ {int** inst_tab; int rhythm; int* instvol_r; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_ar_dr (size_t,int) ; 
 int /*<<< orphan*/  set_ksl_tl (size_t,int) ; 
 int /*<<< orphan*/  set_ksl_wave_fb (size_t,int) ; 
 int /*<<< orphan*/  set_mul (size_t,int) ; 
 int /*<<< orphan*/  set_sl_rr (size_t,int) ; 
 TYPE_1__ ym2413 ; 

__attribute__((used)) static void update_instrument_zero(UINT8 r)
{
  UINT8* inst = &ym2413.inst_tab[0][0]; /* point to user instrument */
  UINT32 chan;

  UINT32 chan_max = 9;
  if (ym2413.rhythm & 0x20)
    chan_max=6;

  switch(r&7)
  {
    case 0:
      for (chan=0; chan<chan_max; chan++)
      {
        if ((ym2413.instvol_r[chan]&0xf0)==0)
        {
          set_mul(chan*2, inst[0]);
        }
      }
      break;

    case 1:
      for (chan=0; chan<chan_max; chan++)
      {
        if ((ym2413.instvol_r[chan]&0xf0)==0)
        {
          set_mul(chan*2+1, inst[1]);
        }
      }
      break;

    case 2:
      for (chan=0; chan<chan_max; chan++)
      {
        if ((ym2413.instvol_r[chan]&0xf0)==0)
        {
          set_ksl_tl(chan, inst[2]);
        }
      }
      break;

    case 3:
      for (chan=0; chan<chan_max; chan++)
      {
        if ((ym2413.instvol_r[chan]&0xf0)==0)
        {
          set_ksl_wave_fb(chan, inst[3]);
        }
      }
      break;

    case 4:
      for (chan=0; chan<chan_max; chan++)
      {
        if ((ym2413.instvol_r[chan]&0xf0)==0)
        {
          set_ar_dr(chan*2, inst[4]);
        }
      }
      break;

    case 5:
      for (chan=0; chan<chan_max; chan++)
      {
        if ((ym2413.instvol_r[chan]&0xf0)==0)
        {
          set_ar_dr(chan*2+1, inst[5]);
        }
      }
      break;

    case 6:
      for (chan=0; chan<chan_max; chan++)
      {
        if ((ym2413.instvol_r[chan]&0xf0)==0)
        {
          set_sl_rr(chan*2, inst[6]);
        }
      }
      break;

    case 7:
      for (chan=0; chan<chan_max; chan++)
      {
        if ((ym2413.instvol_r[chan]&0xf0)==0)
        {
          set_sl_rr(chan*2+1, inst[7]);
        }
      }
      break;
  }
}