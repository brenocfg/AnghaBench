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
struct qcam_device {int /*<<< orphan*/  pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  parport_write_control (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qc_reset(struct qcam_device *qcam)
{
	parport_write_control(qcam->pport, 0xc);
	parport_write_control(qcam->pport, 0x8);
	mdelay(1);
	parport_write_control(qcam->pport, 0xc);
	mdelay(1);
}