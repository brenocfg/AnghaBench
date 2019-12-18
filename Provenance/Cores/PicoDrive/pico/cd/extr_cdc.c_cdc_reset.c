#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* s68k_regs; } ;
struct TYPE_3__ {int ifstat; int ifctrl; int* ctrl; int* stat; int** head; scalar_t__ dma_w; scalar_t__ cycles; } ;

/* Variables and functions */
 TYPE_2__* Pico_mcd ; 
 TYPE_1__ cdc ; 

void cdc_reset(void)
{
  /* reset CDC register index */
  Pico_mcd->s68k_regs[0x04+1] = 0x00;

  /* reset CDC registers */
  cdc.ifstat  = 0xff;
  cdc.ifctrl  = 0x00;
  cdc.ctrl[0] = 0x00;
  cdc.ctrl[1] = 0x00;
  cdc.stat[0] = 0x00;
  cdc.stat[1] = 0x00;
  cdc.stat[2] = 0x00;
  cdc.stat[3] = 0x80;
  cdc.head[0][0] = 0x00;
  cdc.head[0][1] = 0x00;
  cdc.head[0][2] = 0x00;
  cdc.head[0][3] = 0x01;
  cdc.head[1][0] = 0x00;
  cdc.head[1][1] = 0x00;
  cdc.head[1][2] = 0x00;
  cdc.head[1][3] = 0x00;

  /* reset CDC cycle counter */
  cdc.cycles = 0;

  /* DMA transfer disabled */
  cdc.dma_w = 0;
}