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
struct cx24123_state {int dummy; } ;
typedef  int /*<<< orphan*/  fe_spectral_inversion_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int cx24123_readreg (struct cx24123_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int cx24123_get_inversion(struct cx24123_state *state,
	fe_spectral_inversion_t *inversion)
{
	u8 val;

	val = cx24123_readreg(state, 0x1b) >> 7;

	if (val == 0) {
		dprintk("read inversion off\n");
		*inversion = INVERSION_OFF;
	} else {
		dprintk("read inversion on\n");
		*inversion = INVERSION_ON;
	}

	return 0;
}