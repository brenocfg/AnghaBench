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
struct nxt200x_state {int dummy; } ;
struct dvb_frontend {struct nxt200x_state* demodulator_priv; } ;
typedef  int /*<<< orphan*/  fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_HAS_CARRIER ; 
 int /*<<< orphan*/  FE_HAS_LOCK ; 
 int /*<<< orphan*/  FE_HAS_SIGNAL ; 
 int /*<<< orphan*/  FE_HAS_SYNC ; 
 int /*<<< orphan*/  FE_HAS_VITERBI ; 
 int /*<<< orphan*/  nxt200x_readbytes (struct nxt200x_state*,int,int*,int) ; 

__attribute__((used)) static int nxt200x_read_status(struct dvb_frontend* fe, fe_status_t* status)
{
	struct nxt200x_state* state = fe->demodulator_priv;
	u8 lock;
	nxt200x_readbytes(state, 0x31, &lock, 1);

	*status = 0;
	if (lock & 0x20) {
		*status |= FE_HAS_SIGNAL;
		*status |= FE_HAS_CARRIER;
		*status |= FE_HAS_VITERBI;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_LOCK;
	}
	return 0;
}