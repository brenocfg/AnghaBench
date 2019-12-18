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
struct mpsc_port_info {scalar_t__ brg_base_p; scalar_t__ sdma_base_p; scalar_t__ mpsc_base_p; int /*<<< orphan*/ * brg_base; int /*<<< orphan*/ * sdma_base; int /*<<< orphan*/ * mpsc_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPSC_BRG_REG_BLOCK_SIZE ; 
 int /*<<< orphan*/  MPSC_REG_BLOCK_SIZE ; 
 int /*<<< orphan*/  MPSC_SDMA_REG_BLOCK_SIZE ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpsc_drv_unmap_regs(struct mpsc_port_info *pi)
{
	if (!pi->mpsc_base) {
		iounmap(pi->mpsc_base);
		release_mem_region(pi->mpsc_base_p, MPSC_REG_BLOCK_SIZE);
	}
	if (!pi->sdma_base) {
		iounmap(pi->sdma_base);
		release_mem_region(pi->sdma_base_p, MPSC_SDMA_REG_BLOCK_SIZE);
	}
	if (!pi->brg_base) {
		iounmap(pi->brg_base);
		release_mem_region(pi->brg_base_p, MPSC_BRG_REG_BLOCK_SIZE);
	}

	pi->mpsc_base = NULL;
	pi->sdma_base = NULL;
	pi->brg_base = NULL;

	pi->mpsc_base_p = 0;
	pi->sdma_base_p = 0;
	pi->brg_base_p = 0;
}