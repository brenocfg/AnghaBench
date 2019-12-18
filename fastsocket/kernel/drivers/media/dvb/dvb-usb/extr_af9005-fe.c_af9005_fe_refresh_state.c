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
struct dvb_frontend {struct af9005_fe_state* demodulator_priv; } ;
struct af9005_fe_state {scalar_t__ next_status_check; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ af9005_get_statistic (struct dvb_frontend*) ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int af9005_fe_refresh_state(struct dvb_frontend *fe)
{
	struct af9005_fe_state *state = fe->demodulator_priv;
	if (time_after(jiffies, state->next_status_check)) {
		deb_info("REFRESH STATE\n");

		/* statistics */
		if (af9005_get_statistic(fe))
			err("get_statistic_failed");
		state->next_status_check = jiffies + 250 * HZ / 1000;
	}
	return 0;
}