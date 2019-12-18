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
struct ix_sa_dir {int /*<<< orphan*/  npe_ctx; int /*<<< orphan*/  npe_ctx_phys; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ctx_pool ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_sa_dir (struct ix_sa_dir*) ; 

__attribute__((used)) static int init_sa_dir(struct ix_sa_dir *dir)
{
	dir->npe_ctx = dma_pool_alloc(ctx_pool, GFP_KERNEL, &dir->npe_ctx_phys);
	if (!dir->npe_ctx) {
		return -ENOMEM;
	}
	reset_sa_dir(dir);
	return 0;
}