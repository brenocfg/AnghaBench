#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct kd_storage_buffers {int dummy; } ;
struct kd_bufinfo {int dummy; } ;
struct TYPE_6__ {scalar_t__ kdsb_size; scalar_t__ kdsb_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_5__ {int kdebug_cpus; int /*<<< orphan*/  kdebug_flags; int /*<<< orphan*/ * kdebug_iops; TYPE_1__ kds_free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDBG_BUFINIT ; 
 int KDCOPYBUF_SIZE ; 
 int /*<<< orphan*/  KDS_PTR_NULL ; 
 TYPE_3__* kd_bufs ; 
 TYPE_2__ kd_ctrl_page ; 
 int /*<<< orphan*/ * kdbip ; 
 int /*<<< orphan*/ * kdcopybuf ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int n_storage_buffers ; 

__attribute__((used)) static void
delete_buffers(void)
{
	unsigned int i;
	
	if (kd_bufs) {
		for (i = 0; i < n_storage_buffers; i++) {
			if (kd_bufs[i].kdsb_addr) {
				kmem_free(kernel_map, (vm_offset_t)kd_bufs[i].kdsb_addr, (vm_size_t)kd_bufs[i].kdsb_size);
			}
		}
		kmem_free(kernel_map, (vm_offset_t)kd_bufs, (vm_size_t)(n_storage_buffers * sizeof(struct kd_storage_buffers)));

		kd_bufs = NULL;
		n_storage_buffers = 0;
	}
	if (kdcopybuf) {
		kmem_free(kernel_map, (vm_offset_t)kdcopybuf, KDCOPYBUF_SIZE);

		kdcopybuf = NULL;
	}
	kd_ctrl_page.kds_free_list.raw = KDS_PTR_NULL;

	if (kdbip) {
		kmem_free(kernel_map, (vm_offset_t)kdbip, sizeof(struct kd_bufinfo) * kd_ctrl_page.kdebug_cpus);
		
		kdbip = NULL;
	}
        kd_ctrl_page.kdebug_iops = NULL;
	kd_ctrl_page.kdebug_cpus = 0;
	kd_ctrl_page.kdebug_flags &= ~KDBG_BUFINIT;
}