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

/* Variables and functions */
 int IB_QPS_ERR ; 
 int IB_QPS_RESET ; 

__attribute__((used)) static const char *to_ib_state_str(int ib_state)
{
	static const char *state_str[] = {
		"IB_QPS_RESET",
		"IB_QPS_INIT",
		"IB_QPS_RTR",
		"IB_QPS_RTS",
		"IB_QPS_SQD",
		"IB_QPS_SQE",
		"IB_QPS_ERR"
	};
	if (ib_state < IB_QPS_RESET ||
	    ib_state > IB_QPS_ERR)
		return "<invalid IB QP state>";

	ib_state -= IB_QPS_RESET;
	return state_str[ib_state];
}