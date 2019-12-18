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
struct nxt6000_state {int dummy; } ;
typedef  int fe_spectral_inversion_t ;

/* Variables and functions */
 int EINVAL ; 
#define  INVERSION_OFF 129 
#define  INVERSION_ON 128 
 int ITBINV ; 
 int /*<<< orphan*/  OFDM_ITB_CTL ; 
 int nxt6000_writereg (struct nxt6000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nxt6000_set_inversion(struct nxt6000_state* state, fe_spectral_inversion_t inversion)
{
	switch (inversion) {

	case INVERSION_OFF:
		return nxt6000_writereg(state, OFDM_ITB_CTL, 0x00);

	case INVERSION_ON:
		return nxt6000_writereg(state, OFDM_ITB_CTL, ITBINV);

	default:
		return -EINVAL;

	}
}