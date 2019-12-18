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
struct mt312_state {int dummy; } ;
struct dvb_frontend {struct mt312_state* demodulator_priv; } ;
typedef  int /*<<< orphan*/  status ;
typedef  int /*<<< orphan*/  fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_HAS_CARRIER ; 
 int /*<<< orphan*/  FE_HAS_LOCK ; 
 int /*<<< orphan*/  FE_HAS_SIGNAL ; 
 int /*<<< orphan*/  FE_HAS_SYNC ; 
 int /*<<< orphan*/  FE_HAS_VITERBI ; 
 int /*<<< orphan*/  QPSK_STAT_H ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int) ; 
 int mt312_read (struct mt312_state*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int mt312_read_status(struct dvb_frontend *fe, fe_status_t *s)
{
	struct mt312_state *state = fe->demodulator_priv;
	int ret;
	u8 status[3];

	*s = 0;

	ret = mt312_read(state, QPSK_STAT_H, status, sizeof(status));
	if (ret < 0)
		return ret;

	dprintk("QPSK_STAT_H: 0x%02x, QPSK_STAT_L: 0x%02x,"
		" FEC_STATUS: 0x%02x\n", status[0], status[1], status[2]);

	if (status[0] & 0xc0)
		*s |= FE_HAS_SIGNAL;	/* signal noise ratio */
	if (status[0] & 0x04)
		*s |= FE_HAS_CARRIER;	/* qpsk carrier lock */
	if (status[2] & 0x02)
		*s |= FE_HAS_VITERBI;	/* viterbi lock */
	if (status[2] & 0x04)
		*s |= FE_HAS_SYNC;	/* byte align lock */
	if (status[0] & 0x01)
		*s |= FE_HAS_LOCK;	/* qpsk lock */

	return 0;
}