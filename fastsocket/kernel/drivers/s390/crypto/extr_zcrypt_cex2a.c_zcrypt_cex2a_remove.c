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
struct zcrypt_ops {int dummy; } ;
struct zcrypt_device {struct zcrypt_ops* ops; } ;
struct ap_device {struct zcrypt_device* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  zcrypt_device_unregister (struct zcrypt_device*) ; 
 int /*<<< orphan*/  zcrypt_msgtype_release (struct zcrypt_ops*) ; 

__attribute__((used)) static void zcrypt_cex2a_remove(struct ap_device *ap_dev)
{
	struct zcrypt_device *zdev = ap_dev->private;
	struct zcrypt_ops *zops = zdev->ops;

	zcrypt_device_unregister(zdev);
	zcrypt_msgtype_release(zops);
}