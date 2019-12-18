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
typedef  int u16 ;
struct s921_state {int dummy; } ;
struct dvb_frontend {struct s921_state* demodulator_priv; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int FE_HAS_LOCK ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int s921_read_status (struct dvb_frontend*,int*) ; 
 int s921_readreg (struct s921_state*,int) ; 

__attribute__((used)) static int s921_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	fe_status_t	status;
	struct s921_state *state = fe->demodulator_priv;
	int rc;

	/* FIXME: Use the proper register for it... 0x80? */
	rc = s921_read_status(fe, &status);
	if (rc < 0)
		return rc;

	*strength = (status & FE_HAS_LOCK) ? 0xffff : 0;

	dprintk("strength = 0x%04x\n", *strength);

	rc = s921_readreg(state, 0x01);
	dprintk("status 0x01: %02x\n", rc);

	rc = s921_readreg(state, 0x80);
	dprintk("status 0x80: %02x\n", rc);

	rc = s921_readreg(state, 0x32);
	dprintk("status 0x32: %02x\n", rc);

	return 0;
}