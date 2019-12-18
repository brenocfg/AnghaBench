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
struct virtqueue {struct kvm_vqconfig* priv; } ;
struct kvm_vqconfig {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_S390_VIRTIO_NOTIFY ; 
 int /*<<< orphan*/  kvm_hypercall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_notify(struct virtqueue *vq)
{
	struct kvm_vqconfig *config = vq->priv;

	kvm_hypercall1(KVM_S390_VIRTIO_NOTIFY, config->address);
}