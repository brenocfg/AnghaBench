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
 int /*<<< orphan*/  parport_frob_control (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void qcam_set_ack(struct qcam_device *qcam, unsigned int i)
{
	/* note: the QC specs refer to the PCAck pin by voltage, not
	   software level.  PC ports have builtin inverters. */
	parport_frob_control(qcam->pport, 8, i?8:0);
}