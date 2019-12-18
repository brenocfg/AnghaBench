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
typedef  int /*<<< orphan*/  pvr_ptr_t ;
typedef  int /*<<< orphan*/  ptr_t ;
struct TYPE_2__ {int PRINA; int PRINB; int PRIR; int /*<<< orphan*/  TVMD; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDDCVdp2SetPriorityNBG0 (int) ; 
 int /*<<< orphan*/  VIDDCVdp2SetPriorityNBG1 (int) ; 
 int /*<<< orphan*/  VIDDCVdp2SetPriorityNBG2 (int) ; 
 int /*<<< orphan*/  VIDDCVdp2SetPriorityNBG3 (int) ; 
 int /*<<< orphan*/  VIDDCVdp2SetPriorityRBG0 (int) ; 
 int /*<<< orphan*/  VIDDCVdp2SetResolution (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp2Draw (int) ; 
 scalar_t__ Vdp2DrawNBG0 () ; 
 scalar_t__ Vdp2DrawNBG1 () ; 
 scalar_t__ Vdp2DrawNBG2 () ; 
 scalar_t__ Vdp2DrawNBG3 () ; 
 TYPE_1__* Vdp2Regs ; 
 scalar_t__ cur_vdp2 ; 
 int /*<<< orphan*/  dcache_flush_range (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_callback ; 
 int /*<<< orphan*/  dmadone ; 
 int nbg0priority ; 
 int nbg1priority ; 
 int nbg2priority ; 
 int nbg3priority ; 
 int /*<<< orphan*/  pvr_txr_load_dma (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ vdp2_fb ; 
 int vdp2_fbnum ; 
 scalar_t__* vdp2_fbs ; 

__attribute__((used)) static void VIDDCVdp2DrawScreens(void)  {
    int i;

    VIDDCVdp2SetResolution(Vdp2Regs->TVMD);
    VIDDCVdp2SetPriorityNBG0(Vdp2Regs->PRINA & 0x7);
    VIDDCVdp2SetPriorityNBG1((Vdp2Regs->PRINA >> 8) & 0x7);
    VIDDCVdp2SetPriorityNBG2(Vdp2Regs->PRINB & 0x7);
    VIDDCVdp2SetPriorityNBG3((Vdp2Regs->PRINB >> 8) & 0x7);
    VIDDCVdp2SetPriorityRBG0(Vdp2Regs->PRIR & 0x7);

    vdp2_fb = vdp2_fbs[0];
    vdp2_fbnum = 0;

    for(i = 1; i < 8; i++)  {
        if(nbg3priority == i)   {
            if(Vdp2DrawNBG3())  {
                dcache_flush_range((ptr_t)(vdp2_fb), 512 * 256 * 2);
                sem_wait(&dmadone);

                pvr_txr_load_dma(vdp2_fb, (pvr_ptr_t) cur_vdp2, 512 * 256 * 2,
                                 0, dma_callback, 0);

                Vdp2Draw(i);

                cur_vdp2 += 512 * 256 * 2;
                vdp2_fbnum ^= 1;
                vdp2_fb = vdp2_fbs[vdp2_fbnum];
            }
        }
        if(nbg2priority == i)   {
            if(Vdp2DrawNBG2())  {
                dcache_flush_range((ptr_t)(vdp2_fb), 512 * 256 * 2);
                sem_wait(&dmadone);

                pvr_txr_load_dma(vdp2_fb, (pvr_ptr_t) cur_vdp2, 512 * 256 * 2,
                                 0, dma_callback, 0);

                Vdp2Draw(i);

                cur_vdp2 += 512 * 256 * 2;
                vdp2_fbnum ^= 1;
                vdp2_fb = vdp2_fbs[vdp2_fbnum];
            }
        }
        if(nbg1priority == i)   {
            if(Vdp2DrawNBG1())  {
                dcache_flush_range((ptr_t)(vdp2_fb), 512 * 256 * 2);
                sem_wait(&dmadone);

                pvr_txr_load_dma(vdp2_fb, (pvr_ptr_t) cur_vdp2, 512 * 256 * 2,
                                 0, dma_callback, 0);

                Vdp2Draw(i);

                cur_vdp2 += 512 * 256 * 2;
                vdp2_fbnum ^= 1;
                vdp2_fb = vdp2_fbs[vdp2_fbnum];
            }
        }
        if(nbg0priority == i)   {
            if(Vdp2DrawNBG0())  {
                dcache_flush_range((ptr_t)(vdp2_fb), 512 * 256 * 2);
                sem_wait(&dmadone);

                pvr_txr_load_dma(vdp2_fb, (pvr_ptr_t) cur_vdp2, 512 * 256 * 2,
                                 0, dma_callback, 0);

                Vdp2Draw(i);

                cur_vdp2 += 512 * 256 * 2;
                vdp2_fbnum ^= 1;
                vdp2_fb = vdp2_fbs[vdp2_fbnum];
            }
        }
//        if (rbg0priority == i)
//            Vdp2DrawRBG0();
    }
}