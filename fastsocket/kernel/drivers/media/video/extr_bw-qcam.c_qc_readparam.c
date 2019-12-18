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
struct qcam_device {int dummy; } ;

/* Variables and functions */
 int qc_waithand (struct qcam_device*,int) ; 
 int /*<<< orphan*/  write_lpcontrol (struct qcam_device*,int) ; 

__attribute__((used)) static int qc_readparam(struct qcam_device *q)
{
	int n1, n2;
	int cmd;

	write_lpcontrol(q, 6);
	n1 = qc_waithand(q, 1);

	write_lpcontrol(q, 0xe);
	n2 = qc_waithand(q, 0);

	cmd = (n1 & 0xf0) | ((n2 & 0xf0) >> 4);
	return cmd;
}