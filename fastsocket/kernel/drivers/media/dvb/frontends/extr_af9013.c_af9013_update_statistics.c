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
struct dvb_frontend {struct af9013_state* demodulator_priv; } ;
struct af9013_state {scalar_t__ next_statistics_check; } ;

/* Variables and functions */
 int af9013_update_ber_unc (struct dvb_frontend*) ; 
 int af9013_update_signal_strength (struct dvb_frontend*) ; 
 int af9013_update_snr (struct dvb_frontend*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int af9013_update_statistics(struct dvb_frontend *fe)
{
	struct af9013_state *state = fe->demodulator_priv;
	int ret;

	if (time_before(jiffies, state->next_statistics_check))
		return 0;

	/* set minimum statistic update interval */
	state->next_statistics_check = jiffies + msecs_to_jiffies(1200);

	ret = af9013_update_signal_strength(fe);
	if (ret)
		goto error;
	ret = af9013_update_snr(fe);
	if (ret)
		goto error;
	ret = af9013_update_ber_unc(fe);
	if (ret)
		goto error;

error:
	return ret;
}