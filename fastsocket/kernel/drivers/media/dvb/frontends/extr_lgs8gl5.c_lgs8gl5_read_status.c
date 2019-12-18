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
typedef  int u8 ;
struct lgs8gl5_state {int dummy; } ;
struct dvb_frontend {struct lgs8gl5_state* demodulator_priv; } ;
typedef  int /*<<< orphan*/  fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_HAS_CARRIER ; 
 int /*<<< orphan*/  FE_HAS_LOCK ; 
 int /*<<< orphan*/  FE_HAS_SIGNAL ; 
 int /*<<< orphan*/  FE_HAS_SYNC ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int REG_STATUS_LOCK ; 
 int REG_STATUS_SYNC ; 
 int /*<<< orphan*/  REG_STRENGTH ; 
 int REG_STRENGTH_CARRIER ; 
 int REG_STRENGTH_MASK ; 
 int lgs8gl5_read_reg (struct lgs8gl5_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lgs8gl5_read_status(struct dvb_frontend *fe, fe_status_t *status)
{
	struct lgs8gl5_state *state = fe->demodulator_priv;
	u8 level = lgs8gl5_read_reg(state, REG_STRENGTH);
	u8 flags = lgs8gl5_read_reg(state, REG_STATUS);

	*status = 0;

	if ((level & REG_STRENGTH_MASK) > 0)
		*status |= FE_HAS_SIGNAL;
	if (level & REG_STRENGTH_CARRIER)
		*status |= FE_HAS_CARRIER;
	if (flags & REG_STATUS_SYNC)
		*status |= FE_HAS_SYNC;
	if (flags & REG_STATUS_LOCK)
		*status |= FE_HAS_LOCK;

	return 0;
}