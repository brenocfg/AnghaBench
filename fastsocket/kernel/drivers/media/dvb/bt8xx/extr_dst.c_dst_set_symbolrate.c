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
typedef  int u64 ;
typedef  int u32 ;
struct dst_state {int symbol_rate; scalar_t__ dst_type; int type_flags; int* tx_tuna; int fw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_DEBUG ; 
 int /*<<< orphan*/  DST_INFO ; 
 int DST_TYPE_HAS_OBS_REGS ; 
 int DST_TYPE_HAS_SYMDIV ; 
 scalar_t__ DST_TYPE_IS_CABLE ; 
 scalar_t__ DST_TYPE_IS_SAT ; 
 scalar_t__ DST_TYPE_IS_TERR ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strncmp (int,char*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int dst_set_symbolrate(struct dst_state *state, u32 srate)
{
	u32 symcalc;
	u64 sval;

	state->symbol_rate = srate;
	if (state->dst_type == DST_TYPE_IS_TERR) {
		return -EOPNOTSUPP;
	}
	dprintk(verbose, DST_INFO, 1, "set symrate %u", srate);
	srate /= 1000;
	if (state->dst_type == DST_TYPE_IS_SAT) {
		if (state->type_flags & DST_TYPE_HAS_SYMDIV) {
			sval = srate;
			sval <<= 20;
			do_div(sval, 88000);
			symcalc = (u32) sval;
			dprintk(verbose, DST_INFO, 1, "set symcalc %u", symcalc);
			state->tx_tuna[5] = (u8) (symcalc >> 12);
			state->tx_tuna[6] = (u8) (symcalc >> 4);
			state->tx_tuna[7] = (u8) (symcalc << 4);
		} else {
			state->tx_tuna[5] = (u8) (srate >> 16) & 0x7f;
			state->tx_tuna[6] = (u8) (srate >> 8);
			state->tx_tuna[7] = (u8) srate;
		}
		state->tx_tuna[8] &= ~0x20;
		if (state->type_flags & DST_TYPE_HAS_OBS_REGS) {
			if (srate > 8000)
				state->tx_tuna[8] |= 0x20;
		}
	} else if (state->dst_type == DST_TYPE_IS_CABLE) {
		dprintk(verbose, DST_DEBUG, 1, "%s", state->fw_name);
		if (!strncmp(state->fw_name, "DCTNEW", 6)) {
			state->tx_tuna[5] = (u8) (srate >> 8);
			state->tx_tuna[6] = (u8) srate;
			state->tx_tuna[7] = 0x00;
		} else if (!strncmp(state->fw_name, "DCT-CI", 6)) {
			state->tx_tuna[5] = 0x00;
			state->tx_tuna[6] = (u8) (srate >> 8);
			state->tx_tuna[7] = (u8) srate;
		}
	}
	return 0;
}