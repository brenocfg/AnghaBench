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
struct vxge_hw_fifo_txd {int /*<<< orphan*/  control_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_HW_FIFO_TXD_LSO_EN ; 
 int /*<<< orphan*/  VXGE_HW_FIFO_TXD_LSO_MSS (int) ; 

__attribute__((used)) static inline void vxge_hw_fifo_txdl_mss_set(void *txdlh, int mss)
{
	struct vxge_hw_fifo_txd *txdp = (struct vxge_hw_fifo_txd *)txdlh;

	txdp->control_0 |= VXGE_HW_FIFO_TXD_LSO_EN;
	txdp->control_0 |= VXGE_HW_FIFO_TXD_LSO_MSS(mss);
}