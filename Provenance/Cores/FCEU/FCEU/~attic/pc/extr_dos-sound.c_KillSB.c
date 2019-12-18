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
 int /*<<< orphan*/  KillDMABuffer () ; 
 int PICMask ; 
 int /*<<< orphan*/  ResetDSP () ; 
 int /*<<< orphan*/  ResetVectors () ; 
 int SBIRQ ; 
 int /*<<< orphan*/  WriteDSP (int) ; 
 scalar_t__ format ; 
 scalar_t__ hsmode ; 
 int /*<<< orphan*/  outportb (int,int) ; 

void KillSB(void)
{
 if(hsmode)
  ResetDSP();                   /* High-speed mode requires a DSP reset. */
 else
  WriteDSP(format?0xD9:0xDA);    /* Exit auto-init DMA transfer mode. */ 
 WriteDSP(0xD3);                /* Turn speaker off. */

 outportb((SBIRQ>7)?0xA1:0x21,PICMask|(1<<(SBIRQ&7)));
 ResetVectors();
 outportb((SBIRQ>7)?0xA1:0x21,PICMask);
 KillDMABuffer();
}