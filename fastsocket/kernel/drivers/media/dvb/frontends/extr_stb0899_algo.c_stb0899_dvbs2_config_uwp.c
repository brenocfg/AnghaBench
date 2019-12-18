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
typedef  int /*<<< orphan*/  u32 ;
struct stb0899_internal {int /*<<< orphan*/  av_frame_fine; int /*<<< orphan*/  av_frame_coarse; } ;
struct stb0899_state {struct stb0899_config* config; struct stb0899_internal internal; } ;
struct stb0899_config {int /*<<< orphan*/  sof_search_timeout; int /*<<< orphan*/  uwp_threshold_track; int /*<<< orphan*/  uwp_threshold_acq; int /*<<< orphan*/  miss_threshold; int /*<<< orphan*/  uwp_threshold_sof; int /*<<< orphan*/  esno_quant; int /*<<< orphan*/  esno_ave; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_COARSE_TRK ; 
 int /*<<< orphan*/  FE_FINE_TRK ; 
 int /*<<< orphan*/  SOF_SEARCH_TIMEOUT ; 
 int /*<<< orphan*/  SOF_SRCH_TO ; 
 int /*<<< orphan*/  STB0899_BASE_SOF_SRCH_TO ; 
 int /*<<< orphan*/  STB0899_BASE_UWP_CNTRL1 ; 
 int /*<<< orphan*/  STB0899_BASE_UWP_CNTRL2 ; 
 int /*<<< orphan*/  STB0899_BASE_UWP_CNTRL3 ; 
 int /*<<< orphan*/  STB0899_OFF0_SOF_SRCH_TO ; 
 int /*<<< orphan*/  STB0899_OFF0_UWP_CNTRL1 ; 
 int /*<<< orphan*/  STB0899_OFF0_UWP_CNTRL2 ; 
 int /*<<< orphan*/  STB0899_OFF0_UWP_CNTRL3 ; 
 int /*<<< orphan*/  STB0899_READ_S2REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UWP_CNTRL1 ; 
 int /*<<< orphan*/  UWP_CNTRL2 ; 
 int /*<<< orphan*/  UWP_CNTRL3 ; 
 int /*<<< orphan*/  UWP_ESN0_AVE ; 
 int /*<<< orphan*/  UWP_ESN0_QUANT ; 
 int /*<<< orphan*/  UWP_MISS_TH ; 
 int /*<<< orphan*/  UWP_TH_ACQ ; 
 int /*<<< orphan*/  UWP_TH_SOF ; 
 int /*<<< orphan*/  UWP_TH_TRACK ; 
 int /*<<< orphan*/  stb0899_write_s2reg (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stb0899_dvbs2_config_uwp(struct stb0899_state *state)
{
	struct stb0899_internal *internal = &state->internal;
	struct stb0899_config *config = state->config;
	u32 uwp1, uwp2, uwp3, reg;

	uwp1 = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_CNTRL1);
	uwp2 = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_CNTRL2);
	uwp3 = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_CNTRL3);

	STB0899_SETFIELD_VAL(UWP_ESN0_AVE, uwp1, config->esno_ave);
	STB0899_SETFIELD_VAL(UWP_ESN0_QUANT, uwp1, config->esno_quant);
	STB0899_SETFIELD_VAL(UWP_TH_SOF, uwp1, config->uwp_threshold_sof);

	STB0899_SETFIELD_VAL(FE_COARSE_TRK, uwp2, internal->av_frame_coarse);
	STB0899_SETFIELD_VAL(FE_FINE_TRK, uwp2, internal->av_frame_fine);
	STB0899_SETFIELD_VAL(UWP_MISS_TH, uwp2, config->miss_threshold);

	STB0899_SETFIELD_VAL(UWP_TH_ACQ, uwp3, config->uwp_threshold_acq);
	STB0899_SETFIELD_VAL(UWP_TH_TRACK, uwp3, config->uwp_threshold_track);

	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_UWP_CNTRL1, STB0899_OFF0_UWP_CNTRL1, uwp1);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_UWP_CNTRL2, STB0899_OFF0_UWP_CNTRL2, uwp2);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_UWP_CNTRL3, STB0899_OFF0_UWP_CNTRL3, uwp3);

	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, SOF_SRCH_TO);
	STB0899_SETFIELD_VAL(SOF_SEARCH_TIMEOUT, reg, config->sof_search_timeout);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_SOF_SRCH_TO, STB0899_OFF0_SOF_SRCH_TO, reg);
}