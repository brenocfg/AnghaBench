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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_init_sem_reg; int /*<<< orphan*/  host_page_num_fn; int /*<<< orphan*/  smem_pg0; int /*<<< orphan*/  smem_page_start; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; } ;
typedef  int /*<<< orphan*/  bfa_status_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ BFA_FALSE ; 
 int /*<<< orphan*/  BFA_STATUS_FAILED ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int PSS_SMEM_PGNUM (int /*<<< orphan*/ ,int) ; 
 int PSS_SMEM_PGOFF (int) ; 
 scalar_t__ bfa_ioc_sem_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_mem_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int swab32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_status_t
bfa_ioc_smem_read(struct bfa_ioc_s *ioc, void *tbuf, u32 soff, u32 sz)
{
	u32 pgnum, loff;
	__be32 r32;
	int i, len;
	u32 *buf = tbuf;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, soff);
	loff = PSS_SMEM_PGOFF(soff);
	bfa_trc(ioc, pgnum);
	bfa_trc(ioc, loff);
	bfa_trc(ioc, sz);

	/*
	 *  Hold semaphore to serialize pll init and fwtrc.
	 */
	if (BFA_FALSE == bfa_ioc_sem_get(ioc->ioc_regs.ioc_init_sem_reg)) {
		bfa_trc(ioc, 0);
		return BFA_STATUS_FAILED;
	}

	writel(pgnum, ioc->ioc_regs.host_page_num_fn);

	len = sz/sizeof(u32);
	bfa_trc(ioc, len);
	for (i = 0; i < len; i++) {
		r32 = bfa_mem_read(ioc->ioc_regs.smem_page_start, loff);
		buf[i] = swab32(r32);
		loff += sizeof(u32);

		/*
		 * handle page offset wrap around
		 */
		loff = PSS_SMEM_PGOFF(loff);
		if (loff == 0) {
			pgnum++;
			writel(pgnum, ioc->ioc_regs.host_page_num_fn);
		}
	}
	writel(PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, 0),
			ioc->ioc_regs.host_page_num_fn);
	/*
	 *  release semaphore.
	 */
	readl(ioc->ioc_regs.ioc_init_sem_reg);
	writel(1, ioc->ioc_regs.ioc_init_sem_reg);

	bfa_trc(ioc, pgnum);
	return BFA_STATUS_OK;
}