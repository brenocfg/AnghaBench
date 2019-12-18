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
typedef  int mptcp_state_t ;

/* Variables and functions */
#define  MPTCPS_CLOSED 137 
#define  MPTCPS_CLOSE_WAIT 136 
#define  MPTCPS_CLOSING 135 
#define  MPTCPS_ESTABLISHED 134 
#define  MPTCPS_FIN_WAIT_1 133 
#define  MPTCPS_FIN_WAIT_2 132 
#define  MPTCPS_LAST_ACK 131 
#define  MPTCPS_LISTEN 130 
#define  MPTCPS_TERMINATE 129 
#define  MPTCPS_TIME_WAIT 128 

__attribute__((used)) static const char *
mptcp_state_to_str(mptcp_state_t state)
{
        const char *c = "UNDEFINED";
	switch (state) {
	case MPTCPS_CLOSED:
		c = "MPTCPS_CLOSED";
		break;
	case MPTCPS_LISTEN:
		c = "MPTCPS_LISTEN";
		break;
	case MPTCPS_ESTABLISHED:
		c = "MPTCPS_ESTABLISHED";
		break;
	case MPTCPS_CLOSE_WAIT:
		c = "MPTCPS_CLOSE_WAIT";
		break;
	case MPTCPS_FIN_WAIT_1:
		c = "MPTCPS_FIN_WAIT_1";
		break;
	case MPTCPS_CLOSING:
		c = "MPTCPS_CLOSING";
		break;
	case MPTCPS_LAST_ACK:
		c = "MPTCPS_LAST_ACK";
		break;
	case MPTCPS_FIN_WAIT_2:
		c = "MPTCPS_FIN_WAIT_2";
		break;
	case MPTCPS_TIME_WAIT:
		c = "MPTCPS_TIME_WAIT";
		break;
	case MPTCPS_TERMINATE:
		c = "MPTCPS_TERMINATE";
		break;
	}
	return (c);
}