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
typedef  int cqev_t ;

/* Variables and functions */
#define  CLASSQ_EV_LINK_BANDWIDTH 132 
#define  CLASSQ_EV_LINK_DOWN 131 
#define  CLASSQ_EV_LINK_LATENCY 130 
#define  CLASSQ_EV_LINK_MTU 129 
#define  CLASSQ_EV_LINK_UP 128 

const char *
ifclassq_ev2str(cqev_t ev)
{
	const char *c;

	switch (ev) {
	case CLASSQ_EV_LINK_BANDWIDTH:
		c = "LINK_BANDWIDTH";
		break;

	case CLASSQ_EV_LINK_LATENCY:
		c = "LINK_LATENCY";
		break;

	case CLASSQ_EV_LINK_MTU:
		c = "LINK_MTU";
		break;

	case CLASSQ_EV_LINK_UP:
		c = "LINK_UP";
		break;

	case CLASSQ_EV_LINK_DOWN:
		c = "LINK_DOWN";
		break;

	default:
		c = "UNKNOWN";
		break;
	}

	return (c);
}