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
struct firedtv {int /*<<< orphan*/  voltage; } ;
struct dvb_frontend {struct firedtv* sec_priv; } ;
typedef  int /*<<< orphan*/  fe_sec_voltage_t ;

/* Variables and functions */

__attribute__((used)) static int fdtv_set_voltage(struct dvb_frontend *fe,
			    fe_sec_voltage_t voltage)
{
	struct firedtv *fdtv = fe->sec_priv;

	fdtv->voltage = voltage;
	return 0;
}