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
typedef  int ev_ret_t ;

/* Variables and functions */
#define  MPTS_EVRET_CONNECT_PENDING 131 
#define  MPTS_EVRET_DELETE 130 
#define  MPTS_EVRET_DISCONNECT_FALLBACK 129 
#define  MPTS_EVRET_OK 128 

__attribute__((used)) static const char *
mptcp_evret2str(ev_ret_t ret)
{
	const char *c = "UNKNOWN";

	switch (ret) {
	case MPTS_EVRET_DELETE:
		c = "MPTS_EVRET_DELETE";
		break;
	case MPTS_EVRET_CONNECT_PENDING:
		c = "MPTS_EVRET_CONNECT_PENDING";
		break;
	case MPTS_EVRET_DISCONNECT_FALLBACK:
		c = "MPTS_EVRET_DISCONNECT_FALLBACK";
		break;
	case MPTS_EVRET_OK:
		c = "MPTS_EVRET_OK";
		break;
	default:
		break;
	}
	return (c);
}