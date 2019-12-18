#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * zd_range_lock; } ;
typedef  TYPE_1__ ztest_ds_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  rll_t ;
typedef  int /*<<< orphan*/  rl_type_t ;
struct TYPE_7__ {int rl_object; int rl_offset; int rl_size; int /*<<< orphan*/ * rl_lock; } ;
typedef  TYPE_2__ rl_t ;

/* Variables and functions */
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int ZTEST_RANGE_LOCKS ; 
 TYPE_2__* umem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_rll_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rl_t *
ztest_range_lock(ztest_ds_t *zd, uint64_t object, uint64_t offset,
    uint64_t size, rl_type_t type)
{
	uint64_t hash = object ^ (offset % (ZTEST_RANGE_LOCKS + 1));
	rll_t *rll = &zd->zd_range_lock[hash & (ZTEST_RANGE_LOCKS - 1)];
	rl_t *rl;

	rl = umem_alloc(sizeof (*rl), UMEM_NOFAIL);
	rl->rl_object = object;
	rl->rl_offset = offset;
	rl->rl_size = size;
	rl->rl_lock = rll;

	ztest_rll_lock(rll, type);

	return (rl);
}