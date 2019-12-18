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
struct dvb_frontend {struct dib3000mc_state* demodulator_priv; } ;
struct dib3000mc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib3000mc_read_word (struct dib3000mc_state*,int) ; 

__attribute__((used)) static int dib3000mc_read_unc_blocks(struct dvb_frontend *fe, u32 *unc)
{
	struct dib3000mc_state *state = fe->demodulator_priv;
	*unc = dib3000mc_read_word(state, 508);
	return 0;
}