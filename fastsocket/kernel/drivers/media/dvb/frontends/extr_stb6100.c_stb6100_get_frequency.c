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
typedef  int u32 ;
struct stb6100_state {int reference; int frequency; } ;
struct dvb_frontend {struct stb6100_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
 size_t STB6100_K ; 
 int STB6100_K_NF_MSB ; 
 int STB6100_K_PSD2 ; 
 int STB6100_K_PSD2_SHIFT ; 
 size_t STB6100_NF_LSB ; 
 size_t STB6100_NI ; 
 int STB6100_NUMREGS ; 
 size_t STB6100_VCO ; 
 int STB6100_VCO_ODIV ; 
 int STB6100_VCO_ODIV_SHIFT ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int,int,int,int,int,int) ; 
 int stb6100_read_regs (struct stb6100_state*,int*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int stb6100_get_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	int rc;
	u32 nint, nfrac, fvco;
	int psd2, odiv;
	struct stb6100_state *state = fe->tuner_priv;
	u8 regs[STB6100_NUMREGS];

	rc = stb6100_read_regs(state, regs);
	if (rc < 0)
		return rc;

	odiv = (regs[STB6100_VCO] & STB6100_VCO_ODIV) >> STB6100_VCO_ODIV_SHIFT;
	psd2 = (regs[STB6100_K] & STB6100_K_PSD2) >> STB6100_K_PSD2_SHIFT;
	nint = regs[STB6100_NI];
	nfrac = ((regs[STB6100_K] & STB6100_K_NF_MSB) << 8) | regs[STB6100_NF_LSB];
	fvco = (nfrac * state->reference >> (9 - psd2)) + (nint * state->reference << psd2);
	*frequency = state->frequency = fvco >> (odiv + 1);

	dprintk(verbose, FE_DEBUG, 1,
		"frequency = %u kHz, odiv = %u, psd2 = %u, fxtal = %u kHz, fvco = %u kHz, N(I) = %u, N(F) = %u",
		state->frequency, odiv, psd2, state->reference,	fvco, nint, nfrac);
	return 0;
}