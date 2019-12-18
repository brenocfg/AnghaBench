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
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ IWL_POLL_INTERVAL ; 
 int iwl_read_direct32 (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

int iwl_poll_direct_bit(struct iwl_trans *trans, u32 addr, u32 mask,
			int timeout)
{
	int t = 0;

	do {
		if ((iwl_read_direct32(trans, addr) & mask) == mask)
			return t;
		udelay(IWL_POLL_INTERVAL);
		t += IWL_POLL_INTERVAL;
	} while (t < timeout);

	return -ETIMEDOUT;
}