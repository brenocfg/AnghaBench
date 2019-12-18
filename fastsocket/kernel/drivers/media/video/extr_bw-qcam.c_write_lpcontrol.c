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
 int /*<<< orphan*/  parport_data_forward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_data_reverse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_write_control (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void write_lpcontrol(struct qcam_device *q, int d)
{
	if (d & 0x20) {
		/* Set bidirectional mode to reverse (data in) */
		parport_data_reverse(q->pport);
	} else {
		/* Set bidirectional mode to forward (data out) */
		parport_data_forward(q->pport);
	}

	/* Now issue the regular port command, but strip out the
	 * direction flag */
	d &= ~0x20;
	parport_write_control(q->pport, d);
}