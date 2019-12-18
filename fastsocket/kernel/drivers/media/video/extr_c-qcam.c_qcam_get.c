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
 int qcam_read_data (struct qcam_device*) ; 
 scalar_t__ qcam_write_data (struct qcam_device*,unsigned int) ; 

__attribute__((used)) static inline int qcam_get(struct qcam_device *qcam, unsigned int cmd)
{
	if (qcam_write_data(qcam, cmd))
		return -1;
	return qcam_read_data(qcam);
}