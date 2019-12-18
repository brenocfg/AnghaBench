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
typedef  int u32 ;
struct mb86a16_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ CNTM_set (struct mb86a16_state*,int,int,int) ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int mb86a16_read (struct mb86a16_state*,int,unsigned char*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  smrt_info_get (struct mb86a16_state*,int) ; 
 int /*<<< orphan*/  smrt_set (struct mb86a16_state*,int) ; 
 int /*<<< orphan*/  srst (struct mb86a16_state*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int signal_det(struct mb86a16_state *state,
		      int smrt,
		      unsigned char *SIG)
{

	int ret ;
	int smrtd ;
	int wait_sym ;

	u32 wait_t;
	unsigned char S[3] ;
	int i ;

	if (*SIG > 45) {
		if (CNTM_set(state, 2, 1, 2) < 0) {
			dprintk(verbose, MB86A16_ERROR, 1, "CNTM set Error");
			return -1;
		}
		wait_sym = 40000;
	} else {
		if (CNTM_set(state, 3, 1, 2) < 0) {
			dprintk(verbose, MB86A16_ERROR, 1, "CNTM set Error");
			return -1;
		}
		wait_sym = 80000;
	}
	for (i = 0; i < 3; i++) {
		if (i == 0)
			smrtd = smrt * 98 / 100;
		else if (i == 1)
			smrtd = smrt;
		else
			smrtd = smrt * 102 / 100;
		smrt_info_get(state, smrtd);
		smrt_set(state, smrtd);
		srst(state);
		wait_t = (wait_sym + 99 * smrtd / 100) / smrtd;
		if (wait_t == 0)
			wait_t = 1;
		msleep_interruptible(10);
		if (mb86a16_read(state, 0x37, &(S[i])) != 2) {
			dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
			return -EREMOTEIO;
		}
	}
	if ((S[1] > S[0] * 112 / 100) &&
	    (S[1] > S[2] * 112 / 100)) {

		ret = 1;
	} else {
		ret = 0;
	}
	*SIG = S[1];

	if (CNTM_set(state, 0, 1, 2) < 0) {
		dprintk(verbose, MB86A16_ERROR, 1, "CNTM set Error");
		return -1;
	}

	return ret;
}