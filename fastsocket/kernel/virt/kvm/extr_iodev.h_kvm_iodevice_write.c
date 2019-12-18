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
struct kvm_io_device {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_2__ {int (* write ) (struct kvm_io_device*,int /*<<< orphan*/ ,int,void const*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct kvm_io_device*,int /*<<< orphan*/ ,int,void const*) ; 

__attribute__((used)) static inline int kvm_iodevice_write(struct kvm_io_device *dev,
				     gpa_t addr, int l, const void *v)
{
	return dev->ops->write ? dev->ops->write(dev, addr, l, v) : -EOPNOTSUPP;
}