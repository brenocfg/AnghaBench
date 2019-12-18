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
typedef  int u32 ;
struct bt878 {int risc_dma; } ;

/* Variables and functions */
 int BT878_AFBUS ; 
 int BT878_AFDSR ; 
 int BT878_AFTRGT ; 
 int /*<<< orphan*/  BT878_AGPIO_DMA_CTL ; 
 int /*<<< orphan*/  BT878_AINT_MASK ; 
 int BT878_AOCERR ; 
 int BT878_APABORT ; 
 int BT878_APPERR ; 
 int BT878_ARIPERR ; 
 int BT878_ARISCI ; 
 int /*<<< orphan*/  BT878_ARISC_START ; 
 int BT878_ASCERR ; 
 int /*<<< orphan*/  bt878_risc_program (struct bt878*,int) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

void bt878_start(struct bt878 *bt, u32 controlreg, u32 op_sync_orin,
		u32 irq_err_ignore)
{
	u32 int_mask;

	dprintk("bt878 debug: bt878_start (ctl=%8.8x)\n", controlreg);
	/* complete the writing of the risc dma program now we have
	 * the card specifics
	 */
	bt878_risc_program(bt, op_sync_orin);
	controlreg &= ~0x1f;
	controlreg |= 0x1b;

	btwrite(bt->risc_dma, BT878_ARISC_START);

	/* original int mask had :
	 *    6    2    8    4    0
	 * 1111 1111 1000 0000 0000
	 * SCERR|OCERR|PABORT|RIPERR|FDSR|FTRGT|FBUS|RISCI
	 * Hacked for DST to:
	 * SCERR | OCERR | FDSR | FTRGT | FBUS | RISCI
	 */
	int_mask = BT878_ASCERR | BT878_AOCERR | BT878_APABORT |
		BT878_ARIPERR | BT878_APPERR | BT878_AFDSR | BT878_AFTRGT |
		BT878_AFBUS | BT878_ARISCI;


	/* ignore pesky bits */
	int_mask &= ~irq_err_ignore;

	btwrite(int_mask, BT878_AINT_MASK);
	btwrite(controlreg, BT878_AGPIO_DMA_CTL);
}