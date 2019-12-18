#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipw_tty {int dummy; } ;
struct ipw_network {int dummy; } ;
struct ipw_hardware {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ dev_node_t ;

/* Variables and functions */
 int IPWIRELESS_PCMCIA_MINORS ; 
 int IPWIRELESS_PCMCIA_MINOR_RANGE ; 
 int IPW_CHANNEL_DIALLER ; 
 int IPW_CHANNEL_RAS ; 
 int /*<<< orphan*/  TTYTYPE_MODEM ; 
 int /*<<< orphan*/  TTYTYPE_MONITOR ; 
 int /*<<< orphan*/  TTYTYPE_RAS_RAW ; 
 scalar_t__ add_tty (TYPE_1__*,int,struct ipw_hardware*,struct ipw_network*,int,int,int /*<<< orphan*/ ) ; 
 struct ipw_tty** ttys ; 

struct ipw_tty *ipwireless_tty_create(struct ipw_hardware *hardware,
				      struct ipw_network *network,
				      dev_node_t *nodes)
{
	int i, j;

	for (i = 0; i < IPWIRELESS_PCMCIA_MINOR_RANGE; i++) {
		int allfree = 1;

		for (j = i; j < IPWIRELESS_PCMCIA_MINORS;
				j += IPWIRELESS_PCMCIA_MINOR_RANGE)
			if (ttys[j] != NULL) {
				allfree = 0;
				break;
			}

		if (allfree) {
			j = i;

			if (add_tty(&nodes[0], j, hardware, network,
					IPW_CHANNEL_DIALLER, IPW_CHANNEL_RAS,
					TTYTYPE_MODEM))
				return NULL;

			j += IPWIRELESS_PCMCIA_MINOR_RANGE;
			if (add_tty(&nodes[1], j, hardware, network,
					IPW_CHANNEL_DIALLER, -1,
					TTYTYPE_MONITOR))
				return NULL;

			j += IPWIRELESS_PCMCIA_MINOR_RANGE;
			if (add_tty(NULL, j, hardware, network,
					IPW_CHANNEL_RAS, -1,
					TTYTYPE_RAS_RAW))
				return NULL;

			nodes[0].next = &nodes[1];
			nodes[1].next = NULL;

			return ttys[i];
		}
	}
	return NULL;
}