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
typedef  int /*<<< orphan*/  v ;
typedef  int /*<<< orphan*/  u32 ;
struct serial_console_data {int /*<<< orphan*/ * close; int /*<<< orphan*/  tstc; int /*<<< orphan*/  getc; int /*<<< orphan*/  putc; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int MPSC_INTR_CAUSE ; 
 int MPSC_INTR_MASK ; 
 int getprop (void*,char*,void**,int) ; 
 void* mpsc_base ; 
 void* mpsc_get_virtreg_of_phandle (void*,char*) ; 
 int /*<<< orphan*/  mpsc_getc ; 
 int /*<<< orphan*/  mpsc_open ; 
 int /*<<< orphan*/  mpsc_putc ; 
 int /*<<< orphan*/  mpsc_stop_dma (char volatile*) ; 
 int /*<<< orphan*/  mpsc_tstc ; 
 int /*<<< orphan*/ * mpscintr_base ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mpsc_console_init(void *devp, struct serial_console_data *scdp)
{
	void *v;
	int n, reg_set;
	volatile char *sdma_base;

	n = getprop(devp, "virtual-reg", &v, sizeof(v));
	if (n != sizeof(v))
		goto err_out;
	mpsc_base = v;

	sdma_base = mpsc_get_virtreg_of_phandle(devp, "sdma");
	if (sdma_base == NULL)
		goto err_out;

	mpscintr_base = mpsc_get_virtreg_of_phandle(devp, "mpscintr");
	if (mpscintr_base == NULL)
		goto err_out;

	n = getprop(devp, "cell-index", &v, sizeof(v));
	if (n != sizeof(v))
		goto err_out;
	reg_set = (int)v;

	mpscintr_base += (reg_set == 0) ? 0x4 : 0xc;

	/* Make sure the mpsc ctlrs are shutdown */
	out_le32((u32 *)(mpscintr_base + MPSC_INTR_CAUSE), 0);
	out_le32((u32 *)(mpscintr_base + MPSC_INTR_CAUSE), 0);
	out_le32((u32 *)(mpscintr_base + MPSC_INTR_MASK), 0);
	out_le32((u32 *)(mpscintr_base + MPSC_INTR_MASK), 0);

	mpsc_stop_dma(sdma_base);

	scdp->open = mpsc_open;
	scdp->putc = mpsc_putc;
	scdp->getc = mpsc_getc;
	scdp->tstc = mpsc_tstc;
	scdp->close = NULL;

	return 0;

err_out:
	return -1;
}