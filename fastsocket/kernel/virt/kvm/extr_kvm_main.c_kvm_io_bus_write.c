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
struct kvm_io_bus {int dev_count; int /*<<< orphan*/ * devs; } ;
struct kvm {int /*<<< orphan*/ * buses; } ;
typedef  int /*<<< orphan*/  gpa_t ;
typedef  enum kvm_bus { ____Placeholder_kvm_bus } kvm_bus ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  kvm_iodevice_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void const*) ; 
 struct kvm_io_bus* rcu_dereference (int /*<<< orphan*/ ) ; 

int kvm_io_bus_write(struct kvm *kvm, enum kvm_bus bus_idx, gpa_t addr,
		     int len, const void *val)
{
	int i;
	struct kvm_io_bus *bus = rcu_dereference(kvm->buses[bus_idx]);
	for (i = 0; i < bus->dev_count; i++)
		if (!kvm_iodevice_write(bus->devs[i], addr, len, val))
			return 0;
	return -EOPNOTSUPP;
}