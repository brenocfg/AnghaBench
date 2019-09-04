#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* tcp_seq ;
struct tcpcb {scalar_t__ snd_numholes; } ;
struct sackhole {void* rxmit; void* end; void* start; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcps_sack_sboverflow; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSIncrementAtomic (scalar_t__*) ; 
 int /*<<< orphan*/  sack_hole_zone ; 
 scalar_t__ tcp_sack_globalholes ; 
 scalar_t__ tcp_sack_globalmaxholes ; 
 scalar_t__ tcp_sack_maxholes ; 
 TYPE_1__ tcpstat ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sackhole *
tcp_sackhole_alloc(struct tcpcb *tp, tcp_seq start, tcp_seq end)
{
	struct sackhole *hole;

	if (tp->snd_numholes >= tcp_sack_maxholes ||
	    tcp_sack_globalholes >= tcp_sack_globalmaxholes) {
		tcpstat.tcps_sack_sboverflow++;
		return NULL;
	}

	hole = (struct sackhole *)zalloc(sack_hole_zone);
	if (hole == NULL)
		return NULL;

	hole->start = start;
	hole->end = end;
	hole->rxmit = start;

	tp->snd_numholes++;
	OSIncrementAtomic(&tcp_sack_globalholes);

	return hole;
}