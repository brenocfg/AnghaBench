#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* SLOT; } ;
typedef  TYPE_2__ YM2413_OPLL_CH ;
struct TYPE_6__ {int noise_rng; TYPE_2__* P_CH; int /*<<< orphan*/ ** inst_tab; scalar_t__ eg_cnt; scalar_t__ eg_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  volume; int /*<<< orphan*/  state; scalar_t__ wavetable; } ;

/* Variables and functions */
 int /*<<< orphan*/  EG_OFF ; 
 int /*<<< orphan*/  MAX_ATT_INDEX ; 
 int /*<<< orphan*/  OPLLWriteReg (int,int) ; 
 int /*<<< orphan*/ ** table ; 
 TYPE_3__ ym2413 ; 

void YM2413ResetChip(void)
{
  int c,s;
  int i;

  ym2413.eg_timer = 0;
  ym2413.eg_cnt   = 0;

  ym2413.noise_rng = 1;  /* noise shift register */


  /* setup instruments table */
  for (i=0; i<19; i++)
  {
    for (c=0; c<8; c++)
    {
      ym2413.inst_tab[i][c] = table[i][c];
    }
  }


  /* reset with register write */
  OPLLWriteReg(0x0f,0); /*test reg*/
  for(i = 0x3f ; i >= 0x10 ; i-- ) OPLLWriteReg(i,0x00);

  /* reset operator parameters */
  for( c = 0 ; c < 9 ; c++ )
  {
    YM2413_OPLL_CH *CH = &ym2413.P_CH[c];
    for(s = 0 ; s < 2 ; s++ )
    {
      /* wave table */
      CH->SLOT[s].wavetable = 0;
      CH->SLOT[s].state     = EG_OFF;
      CH->SLOT[s].volume    = MAX_ATT_INDEX;
    }
  }
}