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
typedef  int /*<<< orphan*/  u8 ;
struct virtio_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  LHCALL_NOTIFY ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  kvm_hypercall1 (int /*<<< orphan*/ ,unsigned long) ; 
 void* lguest_devices ; 
 unsigned long max_pfn ; 
 TYPE_2__* to_lgdev (struct virtio_device*) ; 

__attribute__((used)) static void set_status(struct virtio_device *vdev, u8 status)
{
	unsigned long offset = (void *)to_lgdev(vdev)->desc - lguest_devices;

	/* We set the status. */
	to_lgdev(vdev)->desc->status = status;
	kvm_hypercall1(LHCALL_NOTIFY, (max_pfn << PAGE_SHIFT) + offset);
}