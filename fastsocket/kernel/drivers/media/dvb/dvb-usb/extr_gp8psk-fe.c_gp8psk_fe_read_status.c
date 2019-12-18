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
struct gp8psk_fe_state {int status_check_interval; scalar_t__ lock; } ;
struct dvb_frontend {struct gp8psk_fe_state* demodulator_priv; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  gp8psk_fe_update_status (struct gp8psk_fe_state*) ; 

__attribute__((used)) static int gp8psk_fe_read_status(struct dvb_frontend* fe, fe_status_t *status)
{
	struct gp8psk_fe_state *st = fe->demodulator_priv;
	gp8psk_fe_update_status(st);

	if (st->lock)
		*status = FE_HAS_LOCK | FE_HAS_SYNC | FE_HAS_VITERBI | FE_HAS_SIGNAL | FE_HAS_CARRIER;
	else
		*status = 0;

	if (*status & FE_HAS_LOCK)
		st->status_check_interval = 1000;
	else
		st->status_check_interval = 100;
	return 0;
}