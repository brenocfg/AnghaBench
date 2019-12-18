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
struct s921_state {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {scalar_t__ demodulator_priv; } ;
typedef  int /*<<< orphan*/  fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_HAS_CARRIER ; 
 int /*<<< orphan*/  FE_HAS_LOCK ; 
 int /*<<< orphan*/  FE_HAS_SIGNAL ; 
 int /*<<< orphan*/  FE_HAS_SYNC ; 
 int /*<<< orphan*/  FE_HAS_VITERBI ; 
 int /*<<< orphan*/  ISDB_T_CMD_GET_STATUS ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 
 int /*<<< orphan*/  s921_isdb_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int s921_read_status(struct dvb_frontend *fe, fe_status_t *status)
{
	struct s921_state *state = (struct s921_state *)fe->demodulator_priv;
	unsigned int ret;
	mdelay(5);
	s921_isdb_cmd(&state->dev, ISDB_T_CMD_GET_STATUS, &ret);
	*status = 0;

	printk("status: %02x\n", ret);
	if (ret == 1) {
		*status |= FE_HAS_CARRIER;
		*status |= FE_HAS_VITERBI;
		*status |= FE_HAS_LOCK;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_SIGNAL;
	}

	return 0;
}