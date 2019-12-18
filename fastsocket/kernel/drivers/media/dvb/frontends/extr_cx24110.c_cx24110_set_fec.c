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
struct cx24110_state {int dummy; } ;
typedef  size_t fe_code_rate_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 size_t FEC_AUTO ; 
 int cx24110_readreg (struct cx24110_state*,int) ; 
 int /*<<< orphan*/  cx24110_writereg (struct cx24110_state*,int,int const) ; 

__attribute__((used)) static int cx24110_set_fec (struct cx24110_state* state, fe_code_rate_t fec)
{
/* fixme (low): error handling */

	static const int rate[]={-1,1,2,3,5,7,-1};
	static const int g1[]={-1,0x01,0x02,0x05,0x15,0x45,-1};
	static const int g2[]={-1,0x01,0x03,0x06,0x1a,0x7a,-1};

	/* Well, the AutoAcq engine of the cx24106 and 24110 automatically
	   searches all enabled viterbi rates, and can handle non-standard
	   rates as well. */

	if (fec>FEC_AUTO)
		fec=FEC_AUTO;

	if (fec==FEC_AUTO) { /* (re-)establish AutoAcq behaviour */
		cx24110_writereg(state,0x37,cx24110_readreg(state,0x37)&0xdf);
		/* clear AcqVitDis bit */
		cx24110_writereg(state,0x18,0xae);
		/* allow all DVB standard code rates */
		cx24110_writereg(state,0x05,(cx24110_readreg(state,0x05)&0xf0)|0x3);
		/* set nominal Viterbi rate 3/4 */
		cx24110_writereg(state,0x22,(cx24110_readreg(state,0x22)&0xf0)|0x3);
		/* set current Viterbi rate 3/4 */
		cx24110_writereg(state,0x1a,0x05); cx24110_writereg(state,0x1b,0x06);
		/* set the puncture registers for code rate 3/4 */
		return 0;
	} else {
		cx24110_writereg(state,0x37,cx24110_readreg(state,0x37)|0x20);
		/* set AcqVitDis bit */
		if(rate[fec]>0) {
			cx24110_writereg(state,0x05,(cx24110_readreg(state,0x05)&0xf0)|rate[fec]);
			/* set nominal Viterbi rate */
			cx24110_writereg(state,0x22,(cx24110_readreg(state,0x22)&0xf0)|rate[fec]);
			/* set current Viterbi rate */
			cx24110_writereg(state,0x1a,g1[fec]);
			cx24110_writereg(state,0x1b,g2[fec]);
			/* not sure if this is the right way: I always used AutoAcq mode */
	   } else
		   return -EOPNOTSUPP;
/* fixme (low): which is the correct return code? */
	};
	return 0;
}