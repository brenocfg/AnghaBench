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
typedef  int /*<<< orphan*/  u32 ;
struct stv090x_state {int dummy; } ;
struct dvb_frontend {struct stv090x_state* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int /*<<< orphan*/  DMDSTATE ; 
 int /*<<< orphan*/  DSTATUS ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  HEADER_MODE_FIELD ; 
 int /*<<< orphan*/  LOCKEDVIT_FIELD ; 
 int /*<<< orphan*/  LOCK_DEFINITIF_FIELD ; 
 int /*<<< orphan*/  PDELSTATUS1 ; 
 int /*<<< orphan*/  PKTDELIN_LOCK_FIELD ; 
 int STV090x_GETFIELD_Px (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSFIFO_LINEOK_FIELD ; 
 int /*<<< orphan*/  TSSTATUS ; 
 int /*<<< orphan*/  VSTATUSVIT ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int stv090x_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct stv090x_state *state = fe->demodulator_priv;
	u32 reg;
	u8 search_state;

	reg = STV090x_READ_DEMOD(state, DMDSTATE);
	search_state = STV090x_GETFIELD_Px(reg, HEADER_MODE_FIELD);

	switch (search_state) {
	case 0: /* searching */
	case 1: /* first PLH detected */
	default:
		dprintk(FE_DEBUG, 1, "Status: Unlocked (Searching ..)");
		*status = 0;
		break;

	case 2: /* DVB-S2 mode */
		dprintk(FE_DEBUG, 1, "Delivery system: DVB-S2");
		reg = STV090x_READ_DEMOD(state, DSTATUS);
		if (STV090x_GETFIELD_Px(reg, LOCK_DEFINITIF_FIELD)) {
			reg = STV090x_READ_DEMOD(state, PDELSTATUS1);
			if (STV090x_GETFIELD_Px(reg, PKTDELIN_LOCK_FIELD)) {
				reg = STV090x_READ_DEMOD(state, TSSTATUS);
				if (STV090x_GETFIELD_Px(reg, TSFIFO_LINEOK_FIELD)) {
					*status = FE_HAS_SIGNAL |
						  FE_HAS_CARRIER |
						  FE_HAS_VITERBI |
						  FE_HAS_SYNC |
						  FE_HAS_LOCK;
				}
			}
		}
		break;

	case 3: /* DVB-S1/legacy mode */
		dprintk(FE_DEBUG, 1, "Delivery system: DVB-S");
		reg = STV090x_READ_DEMOD(state, DSTATUS);
		if (STV090x_GETFIELD_Px(reg, LOCK_DEFINITIF_FIELD)) {
			reg = STV090x_READ_DEMOD(state, VSTATUSVIT);
			if (STV090x_GETFIELD_Px(reg, LOCKEDVIT_FIELD)) {
				reg = STV090x_READ_DEMOD(state, TSSTATUS);
				if (STV090x_GETFIELD_Px(reg, TSFIFO_LINEOK_FIELD)) {
					*status = FE_HAS_SIGNAL |
						  FE_HAS_CARRIER |
						  FE_HAS_VITERBI |
						  FE_HAS_SYNC |
						  FE_HAS_LOCK;
				}
			}
		}
		break;
	}

	return 0;
}