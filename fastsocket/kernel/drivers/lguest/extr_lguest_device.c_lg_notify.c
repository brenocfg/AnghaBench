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
struct virtqueue {struct lguest_vq_info* priv; } ;
struct TYPE_2__ {int pfn; } ;
struct lguest_vq_info {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  LHCALL_NOTIFY ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  kvm_hypercall1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lg_notify(struct virtqueue *vq)
{
	/*
	 * We store our virtqueue information in the "priv" pointer of the
	 * virtqueue structure.
	 */
	struct lguest_vq_info *lvq = vq->priv;

	kvm_hypercall1(LHCALL_NOTIFY, lvq->config.pfn << PAGE_SHIFT);
}