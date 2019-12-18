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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* os_reason_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  osr_lock; int /*<<< orphan*/ * osr_kcd_buf; int /*<<< orphan*/  osr_kcd_descriptor; int /*<<< orphan*/  osr_bufsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KCDATA_BUFFER_BEGIN_OS_REASON ; 
 int /*<<< orphan*/  KCFLAG_USE_MEMCOPY ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  OS_REASON_BUFFER_MAX_SIZE ; 
 TYPE_1__* OS_REASON_NULL ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_REASON ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kalloc_noblock_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kalloc_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kcdata_memory_static_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_reason_dealloc_buffer (TYPE_1__*) ; 

__attribute__((used)) static int
os_reason_alloc_buffer_internal(os_reason_t cur_reason, uint32_t osr_bufsize,
				boolean_t can_block)
{
	if (cur_reason == OS_REASON_NULL) {
		return EINVAL;
	}

	if (osr_bufsize > OS_REASON_BUFFER_MAX_SIZE) {
		return EINVAL;
	}

	lck_mtx_lock(&cur_reason->osr_lock);

	os_reason_dealloc_buffer(cur_reason);

	if (osr_bufsize == 0) {
		lck_mtx_unlock(&cur_reason->osr_lock);
		return 0;
	}

	if (can_block) {
		cur_reason->osr_kcd_buf = kalloc_tag(osr_bufsize, VM_KERN_MEMORY_REASON);
		assert(cur_reason->osr_kcd_buf != NULL);
	} else {
		cur_reason->osr_kcd_buf = kalloc_noblock_tag(osr_bufsize, VM_KERN_MEMORY_REASON);
		if (cur_reason->osr_kcd_buf == NULL) {
			lck_mtx_unlock(&cur_reason->osr_lock);
			return ENOMEM;
		}
	}

	bzero(cur_reason->osr_kcd_buf, osr_bufsize);

	cur_reason->osr_bufsize = osr_bufsize;

	if (kcdata_memory_static_init(&cur_reason->osr_kcd_descriptor, (mach_vm_address_t) cur_reason->osr_kcd_buf,
					KCDATA_BUFFER_BEGIN_OS_REASON, osr_bufsize, KCFLAG_USE_MEMCOPY) != KERN_SUCCESS) {
		os_reason_dealloc_buffer(cur_reason);

		lck_mtx_unlock(&cur_reason->osr_lock);
		return EIO;
	}

	lck_mtx_unlock(&cur_reason->osr_lock);

	return 0;
}