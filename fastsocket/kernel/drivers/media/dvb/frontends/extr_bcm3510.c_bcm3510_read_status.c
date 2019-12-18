#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend {struct bcm3510_state* demodulator_priv; } ;
struct TYPE_3__ {scalar_t__ OUT_PLL_LOCK; scalar_t__ FEC_LOCK; scalar_t__ RECEIVER_LOCK; } ;
struct TYPE_4__ {TYPE_1__ STATUS1; } ;
struct bcm3510_state {int status_check_interval; TYPE_2__ status1; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  bcm3510_refresh_state (struct bcm3510_state*) ; 
 int /*<<< orphan*/  deb_info (char*,int) ; 

__attribute__((used)) static int bcm3510_read_status(struct dvb_frontend *fe, fe_status_t *status)
{
	struct bcm3510_state* st = fe->demodulator_priv;
	bcm3510_refresh_state(st);

	*status = 0;
	if (st->status1.STATUS1.RECEIVER_LOCK)
		*status |= FE_HAS_LOCK | FE_HAS_SYNC;

	if (st->status1.STATUS1.FEC_LOCK)
		*status |= FE_HAS_VITERBI;

	if (st->status1.STATUS1.OUT_PLL_LOCK)
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;

	if (*status & FE_HAS_LOCK)
		st->status_check_interval = 1500;
	else /* more frequently checks if no lock has been achieved yet */
		st->status_check_interval = 500;

	deb_info("real_status: %02x\n",*status);
	return 0;
}