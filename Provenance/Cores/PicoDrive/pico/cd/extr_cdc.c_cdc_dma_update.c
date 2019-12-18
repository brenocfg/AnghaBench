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
struct TYPE_3__ {int dbc; int ifstat; int ifctrl; int /*<<< orphan*/  (* dma_w ) (int) ;} ;

/* Variables and functions */
 int BIT_DTBSY ; 
 int BIT_DTEI ; 
 int BIT_DTEIEN ; 
 int BIT_DTEN ; 
 int DMA_BYTES_PER_LINE ; 
 int /*<<< orphan*/  EL_INTS ; 
 int PCDS_IEN5 ; 
 TYPE_2__* Pico_mcd ; 
 int /*<<< orphan*/  SekInterruptS68k (int) ; 
 TYPE_1__ cdc ; 
 int /*<<< orphan*/  do_dma (int /*<<< orphan*/  (*) (int),int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ length ; 
 int /*<<< orphan*/  stub1 (int) ; 

void cdc_dma_update(void)
{
  /* end of DMA transfer ? */
  //if (cdc.dbc < DMA_BYTES_PER_LINE)
  {
    /* transfer remaining words using 16-bit DMA */
    //cdc.dma_w((cdc.dbc + 1) >> 1);
    do_dma(cdc.dma_w, (cdc.dbc + 1) >> 1);

    /* reset data byte counter (DBCH bits 4-7 should be set to 1) */
    cdc.dbc = 0xf000;

    /* clear !DTEN and !DTBSY */
    cdc.ifstat |= (BIT_DTBSY | BIT_DTEN);

    /* pending Data Transfer End interrupt */
    cdc.ifstat &= ~BIT_DTEI;

    /* Data Transfer End interrupt enabled ? */
    if (cdc.ifctrl & BIT_DTEIEN)
    {
      /* level 5 interrupt enabled ? */
      if (Pico_mcd->s68k_regs[0x32+1] & PCDS_IEN5)
      {
        /* update IRQ level */
        elprintf(EL_INTS, "cdc DTE irq 5");
        SekInterruptS68k(5);
      }
    }

    /* clear DSR bit & set EDT bit (SCD register $04) */
    Pico_mcd->s68k_regs[0x04+0] = (Pico_mcd->s68k_regs[0x04+0] & 0x07) | 0x80;

    /* disable DMA transfer */
    cdc.dma_w = 0;
  }
#if 0
  else
  {
    /* transfer all words using 16-bit DMA */
    cdc.dma_w(DMA_BYTES_PER_LINE >> 1);

    /* decrement data byte counter */
    cdc.dbc -= length;
  }
#endif
}