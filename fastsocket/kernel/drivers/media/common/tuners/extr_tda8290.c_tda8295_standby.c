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
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tda8295_agc1_out (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda8295_power (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tda8295_standby(struct dvb_frontend *fe)
{
	tda8295_agc1_out(fe, 0); /* Put AGC in tri-state */

	tda8295_power(fe, 0);
}