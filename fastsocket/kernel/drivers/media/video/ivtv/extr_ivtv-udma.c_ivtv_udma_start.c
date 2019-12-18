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
struct TYPE_2__ {int /*<<< orphan*/  SG_handle; } ;
struct ivtv {int /*<<< orphan*/  i_flags; TYPE_1__ udma; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_DMA (char*) ; 
 int /*<<< orphan*/  IVTV_F_I_DMA ; 
 int /*<<< orphan*/  IVTV_F_I_UDMA ; 
 int /*<<< orphan*/  IVTV_F_I_UDMA_PENDING ; 
 int /*<<< orphan*/  IVTV_REG_DECDMAADDR ; 
 int /*<<< orphan*/  IVTV_REG_DMAXFER ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_sync (int,int /*<<< orphan*/ ) ; 

void ivtv_udma_start(struct ivtv *itv)
{
	IVTV_DEBUG_DMA("start UDMA\n");
	write_reg(itv->udma.SG_handle, IVTV_REG_DECDMAADDR);
	write_reg_sync(read_reg(IVTV_REG_DMAXFER) | 0x01, IVTV_REG_DMAXFER);
	set_bit(IVTV_F_I_DMA, &itv->i_flags);
	set_bit(IVTV_F_I_UDMA, &itv->i_flags);
	clear_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags);
}