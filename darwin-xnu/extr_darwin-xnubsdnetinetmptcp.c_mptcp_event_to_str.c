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
typedef  int uint32_t ;

/* Variables and functions */
#define  MPCE_CLOSE 130 
#define  MPCE_RECV_DATA_ACK 129 
#define  MPCE_RECV_DATA_FIN 128 

__attribute__((used)) static const char *
mptcp_event_to_str(uint32_t event)
{
	const char *c = "UNDEFINED";
	switch (event) {
	case MPCE_CLOSE:
		c = "MPCE_CLOSE";
		break;
	case MPCE_RECV_DATA_ACK:
		c = "MPCE_RECV_DATA_ACK";
		break;
	case MPCE_RECV_DATA_FIN:
		c = "MPCE_RECV_DATA_FIN";
		break;
	}
	return (c);
}