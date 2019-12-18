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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_sa_manager {unsigned int size; int /*<<< orphan*/ * bo; int /*<<< orphan*/ * flist; int /*<<< orphan*/  olist; int /*<<< orphan*/ * hole; int /*<<< orphan*/  domain; int /*<<< orphan*/  wq; } ;
struct radeon_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_CPU ; 
 int /*<<< orphan*/  RADEON_GPU_PAGE_SIZE ; 
 int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int radeon_bo_create (struct radeon_device*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int radeon_sa_bo_manager_init(struct radeon_device *rdev,
			      struct radeon_sa_manager *sa_manager,
			      unsigned size, u32 domain)
{
	int i, r;

	init_waitqueue_head(&sa_manager->wq);
	sa_manager->bo = NULL;
	sa_manager->size = size;
	sa_manager->domain = domain;
	sa_manager->hole = &sa_manager->olist;
	INIT_LIST_HEAD(&sa_manager->olist);
	for (i = 0; i < RADEON_NUM_RINGS; ++i) {
		INIT_LIST_HEAD(&sa_manager->flist[i]);
	}

	r = radeon_bo_create(rdev, size, RADEON_GPU_PAGE_SIZE, true,
			     RADEON_GEM_DOMAIN_CPU, NULL, &sa_manager->bo);
	if (r) {
		dev_err(rdev->dev, "(%d) failed to allocate bo for manager\n", r);
		return r;
	}

	return r;
}