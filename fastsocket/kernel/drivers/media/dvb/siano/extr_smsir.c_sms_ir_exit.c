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
struct TYPE_2__ {scalar_t__ dev; } ;
struct smscore_device_t {TYPE_1__ ir; } ;

/* Variables and functions */
 int /*<<< orphan*/  rc_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  sms_log (char*) ; 

void sms_ir_exit(struct smscore_device_t *coredev)
{
	if (coredev->ir.dev)
		rc_unregister_device(coredev->ir.dev);

	sms_log("");
}