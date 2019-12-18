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
struct dvb_net {int* state; } ;

/* Variables and functions */
 int DVB_NET_DEVICES_MAX ; 

__attribute__((used)) static int get_if(struct dvb_net *dvbnet)
{
	int i;

	for (i=0; i<DVB_NET_DEVICES_MAX; i++)
		if (!dvbnet->state[i])
			break;

	if (i == DVB_NET_DEVICES_MAX)
		return -1;

	dvbnet->state[i]=1;
	return i;
}