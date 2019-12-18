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
typedef  scalar_t__ u8 ;
struct virtio_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* desc; } ;
struct TYPE_3__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  KVM_S390_VIRTIO_SET_STATUS ; 
 int /*<<< orphan*/  kvm_hypercall1 (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_2__* to_kvmdev (struct virtio_device*) ; 

__attribute__((used)) static void kvm_set_status(struct virtio_device *vdev, u8 status)
{
	BUG_ON(!status);
	to_kvmdev(vdev)->desc->status = status;
	kvm_hypercall1(KVM_S390_VIRTIO_SET_STATUS,
		       (unsigned long) to_kvmdev(vdev)->desc);
}