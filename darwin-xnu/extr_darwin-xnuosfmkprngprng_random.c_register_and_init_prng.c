#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/ * prng_fns_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int /*<<< orphan*/  attrs; int /*<<< orphan*/  group; int /*<<< orphan*/  mutex; int /*<<< orphan*/  group_attrs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; TYPE_1__ lock; } ;

/* Variables and functions */
 int ENTROPY_BUFFER_BYTE_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cc_clear (int,int /*<<< orphan*/ **) ; 
 scalar_t__ cpu_number () ; 
 size_t entropy_readall (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ master_cpu ; 
 int nsources ; 
 TYPE_2__ prng ; 
 int /*<<< orphan*/ * prng_fns ; 
 int /*<<< orphan*/  prng_init (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ **) ; 

void
register_and_init_prng(prng_fns_t fns)
{
	uint8_t buf[nsources][ENTROPY_BUFFER_BYTE_SIZE];
	size_t nbytes;

	assert(cpu_number() == master_cpu);
	assert(prng_fns == NULL);

	prng_fns = fns;

	/* make a mutex to control access */
	prng.lock.group_attrs = lck_grp_attr_alloc_init();
	prng.lock.group       = lck_grp_alloc_init("random", prng.lock.group_attrs);
	prng.lock.attrs       = lck_attr_alloc_init();
	prng.lock.mutex       = lck_mtx_alloc_init(prng.lock.group, prng.lock.attrs);

	nbytes = entropy_readall(buf, ENTROPY_BUFFER_BYTE_SIZE);
	(void)prng_init(&prng.ctx, nbytes, buf);
	cc_clear(sizeof(buf), buf);
}