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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int QIB_TWSI_START ; 
 int QIB_TWSI_STOP ; 
 int /*<<< orphan*/  start_seq (struct qib_devdata*) ; 
 int /*<<< orphan*/  stop_cmd (struct qib_devdata*) ; 
 int wr_byte (struct qib_devdata*,int) ; 

__attribute__((used)) static int qib_twsi_wr(struct qib_devdata *dd, int data, int flags)
{
	int ret = 1;
	if (flags & QIB_TWSI_START)
		start_seq(dd);

	ret = wr_byte(dd, data); /* Leaves SCL low (from i2c_ackrcv()) */

	if (flags & QIB_TWSI_STOP)
		stop_cmd(dd);
	return ret;
}