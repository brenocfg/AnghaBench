#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct virtio_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_S390_VIRTIO_RESET ; 
 int /*<<< orphan*/  kvm_hypercall1 (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__* to_kvmdev (struct virtio_device*) ; 

__attribute__((used)) static void kvm_reset(struct virtio_device *vdev)
{
	kvm_hypercall1(KVM_S390_VIRTIO_RESET,
		       (unsigned long) to_kvmdev(vdev)->desc);
}