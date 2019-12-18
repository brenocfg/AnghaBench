#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int w; } ;
struct TYPE_10__ {int ifstat; int ifctrl; TYPE_3__ dbc; int /*<<< orphan*/  (* dma_w ) (int) ;} ;
struct TYPE_9__ {int pending; TYPE_2__* regs; } ;
struct TYPE_6__ {int l; int h; } ;
struct TYPE_7__ {TYPE_1__ byte; } ;

/* Variables and functions */
 int BIT_DTBSY ; 
 int BIT_DTEI ; 
 int BIT_DTEIEN ; 
 int BIT_DTEN ; 
 int DMA_BYTES_PER_LINE ; 
 TYPE_5__ cdc ; 
 int /*<<< orphan*/  s68k_update_irq (int) ; 
 TYPE_4__ scd ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 

void cdc_dma_update(void)
{
  /* maximal transfer length */
  int length = DMA_BYTES_PER_LINE;

  /* end of DMA transfer ? */
  if (cdc.dbc.w < DMA_BYTES_PER_LINE)
  {
    /* transfer remaining words using 16-bit DMA */
    cdc.dma_w((cdc.dbc.w + 1) >> 1);

    /* reset data byte counter (DBCH bits 4-7 should be set to 1) */
    cdc.dbc.w = 0xf000;

    /* clear !DTEN and !DTBSY */
    cdc.ifstat |= (BIT_DTBSY | BIT_DTEN);

    /* pending Data Transfer End interrupt */
    cdc.ifstat &= ~BIT_DTEI;

    /* Data Transfer End interrupt enabled ? */
    if (cdc.ifctrl & BIT_DTEIEN)
    {
      /* pending level 5 interrupt */
      scd.pending |= (1 << 5);

      /* level 5 interrupt enabled ? */
      if (scd.regs[0x32>>1].byte.l & 0x20)
      {
        /* update IRQ level */
        s68k_update_irq((scd.pending & scd.regs[0x32>>1].byte.l) >> 1);
      }
    }

    /* clear DSR bit & set EDT bit (SCD register $04) */
    scd.regs[0x04>>1].byte.h = (scd.regs[0x04>>1].byte.h & 0x07) | 0x80;

    /* disable DMA transfer */
    cdc.dma_w = 0;
  }
  else
  {
    /* transfer all words using 16-bit DMA */
    cdc.dma_w(DMA_BYTES_PER_LINE >> 1);

    /* decrement data byte counter */
    cdc.dbc.w -= length;
  }
}