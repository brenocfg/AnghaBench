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
struct i5400_pvt {int* b0_mtr; int* b1_mtr; } ;

/* Variables and functions */
 int CHANNELS_PER_BRANCH ; 
 int NUM_MTRS_PER_BRANCH ; 
 int /*<<< orphan*/  debugf0 (char*,int) ; 

__attribute__((used)) static int determine_mtr(struct i5400_pvt *pvt, int csrow, int channel)
{
	int mtr;
	int n;

	/* There is one MTR for each slot pair of FB-DIMMs,
	   Each slot pair may be at branch 0 or branch 1.
	 */
	n = csrow;

	if (n >= NUM_MTRS_PER_BRANCH) {
		debugf0("ERROR: trying to access an invalid csrow: %d\n",
			csrow);
		return 0;
	}

	if (channel < CHANNELS_PER_BRANCH)
		mtr = pvt->b0_mtr[n];
	else
		mtr = pvt->b1_mtr[n];

	return mtr;
}