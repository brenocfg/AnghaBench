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
struct kvm_pv_mmu_op_buffer {unsigned int len; void* ptr; } ;

/* Variables and functions */

__attribute__((used)) static void *pv_mmu_peek_buffer(struct kvm_pv_mmu_op_buffer *buffer,
				unsigned len)
{
	if (len > buffer->len)
		return NULL;
	return buffer->ptr;
}