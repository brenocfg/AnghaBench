#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* os_reason_t ;
struct TYPE_5__ {int osr_refcount; int /*<<< orphan*/  osr_lock; int /*<<< orphan*/ * osr_kcd_buf; scalar_t__ osr_bufsize; scalar_t__ osr_flags; int /*<<< orphan*/  osr_code; int /*<<< orphan*/  osr_namespace; } ;

/* Variables and functions */
 TYPE_1__* OS_REASON_NULL ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_reason_debug_disabled ; 
 int /*<<< orphan*/  os_reason_lock_attr ; 
 int /*<<< orphan*/  os_reason_lock_grp ; 
 int /*<<< orphan*/  os_reason_zone ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

os_reason_t
os_reason_create(uint32_t osr_namespace, uint64_t osr_code)
{
	os_reason_t new_reason = OS_REASON_NULL;

	new_reason = (os_reason_t) zalloc(os_reason_zone);
	if (new_reason == OS_REASON_NULL) {
#if OS_REASON_DEBUG
		/*
		 * We rely on OS reasons to communicate important things such
		 * as process exit reason information, we should be aware
		 * when issues prevent us from allocating them.
		 */
		if (os_reason_debug_disabled) {
			kprintf("os_reason_create: failed to allocate reason with namespace: %u, code : %llu\n",
					osr_namespace, osr_code);
		} else {
			panic("os_reason_create: failed to allocate reason with namespace: %u, code: %llu\n",
					osr_namespace, osr_code);
		}
#endif
		return new_reason;
	}

	bzero(new_reason, sizeof(*new_reason));

	new_reason->osr_namespace = osr_namespace;
	new_reason->osr_code = osr_code;
	new_reason->osr_flags = 0;
	new_reason->osr_bufsize = 0;
	new_reason->osr_kcd_buf = NULL;

	lck_mtx_init(&new_reason->osr_lock, os_reason_lock_grp, os_reason_lock_attr);
	new_reason->osr_refcount = 1;

	return new_reason;
}