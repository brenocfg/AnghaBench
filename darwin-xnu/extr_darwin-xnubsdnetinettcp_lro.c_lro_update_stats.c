#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int lro_npkts; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  tcps_lro_largepack; int /*<<< orphan*/  tcps_lro_multpack; int /*<<< orphan*/  tcps_lro_twopack; } ;

/* Variables and functions */
 TYPE_2__ tcpstat ; 

__attribute__((used)) static void
lro_update_stats(struct mbuf *m)
{
	switch(m->m_pkthdr.lro_npkts) {
	case 0: /* fall through */
	case 1: 
		break;
	
	case 2: 
		tcpstat.tcps_lro_twopack++;
		break;
	
	case 3: /* fall through */
	case 4:
		tcpstat.tcps_lro_multpack++;
		break;
	
	default: 
		tcpstat.tcps_lro_largepack++;
		break;
	}
	return;
}