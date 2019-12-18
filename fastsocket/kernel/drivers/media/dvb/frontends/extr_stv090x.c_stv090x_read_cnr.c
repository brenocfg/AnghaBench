#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct stv090x_state {int delsys; } ;
struct dvb_frontend {struct stv090x_state* demodulator_priv; } ;
typedef  int s32 ;
struct TYPE_4__ {int read; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DSTATUS ; 
 int /*<<< orphan*/  LOCK_DEFINITIF_FIELD ; 
 int MAKEWORD16 (int,int) ; 
 int /*<<< orphan*/  NNOSPLHT0 ; 
 int /*<<< orphan*/  NNOSPLHT1 ; 
 int /*<<< orphan*/  NOSDATAT0 ; 
 int /*<<< orphan*/  NOSDATAT1 ; 
 int /*<<< orphan*/  NOSDATAT_UNNORMED_FIELD ; 
 int /*<<< orphan*/  NOSPLHT_NORMED_FIELD ; 
#define  STV090x_DSS 130 
#define  STV090x_DVBS1 129 
#define  STV090x_DVBS2 128 
 void* STV090x_GETFIELD_Px (int,int /*<<< orphan*/ ) ; 
 int STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_1__* stv090x_s1cn_tab ; 
 TYPE_1__* stv090x_s2cn_tab ; 

__attribute__((used)) static int stv090x_read_cnr(struct dvb_frontend *fe, u16 *cnr)
{
	struct stv090x_state *state = fe->demodulator_priv;
	u32 reg_0, reg_1, reg, i;
	s32 val_0, val_1, val = 0;
	u8 lock_f;
	s32 div;
	u32 last;

	switch (state->delsys) {
	case STV090x_DVBS2:
		reg = STV090x_READ_DEMOD(state, DSTATUS);
		lock_f = STV090x_GETFIELD_Px(reg, LOCK_DEFINITIF_FIELD);
		if (lock_f) {
			msleep(5);
			for (i = 0; i < 16; i++) {
				reg_1 = STV090x_READ_DEMOD(state, NNOSPLHT1);
				val_1 = STV090x_GETFIELD_Px(reg_1, NOSPLHT_NORMED_FIELD);
				reg_0 = STV090x_READ_DEMOD(state, NNOSPLHT0);
				val_0 = STV090x_GETFIELD_Px(reg_0, NOSPLHT_NORMED_FIELD);
				val  += MAKEWORD16(val_1, val_0);
				msleep(1);
			}
			val /= 16;
			last = ARRAY_SIZE(stv090x_s2cn_tab) - 1;
			div = stv090x_s2cn_tab[0].read -
			      stv090x_s2cn_tab[last].read;
			*cnr = 0xFFFF - ((val * 0xFFFF) / div);
		}
		break;

	case STV090x_DVBS1:
	case STV090x_DSS:
		reg = STV090x_READ_DEMOD(state, DSTATUS);
		lock_f = STV090x_GETFIELD_Px(reg, LOCK_DEFINITIF_FIELD);
		if (lock_f) {
			msleep(5);
			for (i = 0; i < 16; i++) {
				reg_1 = STV090x_READ_DEMOD(state, NOSDATAT1);
				val_1 = STV090x_GETFIELD_Px(reg_1, NOSDATAT_UNNORMED_FIELD);
				reg_0 = STV090x_READ_DEMOD(state, NOSDATAT0);
				val_0 = STV090x_GETFIELD_Px(reg_0, NOSDATAT_UNNORMED_FIELD);
				val  += MAKEWORD16(val_1, val_0);
				msleep(1);
			}
			val /= 16;
			last = ARRAY_SIZE(stv090x_s1cn_tab) - 1;
			div = stv090x_s1cn_tab[0].read -
			      stv090x_s1cn_tab[last].read;
			*cnr = 0xFFFF - ((val * 0xFFFF) / div);
		}
		break;
	default:
		break;
	}

	return 0;
}