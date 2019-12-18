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
struct fw_device {int dummy; } ;
struct firedtv {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct fw_device* fw_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct fw_device *device_of(struct firedtv *fdtv)
{
	return fw_device(fdtv->device->parent);
}