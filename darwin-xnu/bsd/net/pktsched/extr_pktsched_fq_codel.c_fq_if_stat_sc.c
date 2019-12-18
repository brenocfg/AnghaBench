#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct TYPE_9__ {TYPE_3__* fqs_classq; } ;
typedef  TYPE_2__ fq_if_t ;
struct TYPE_8__ {int /*<<< orphan*/  fcl_byte_cnt; int /*<<< orphan*/  fcl_pkt_cnt; } ;
struct TYPE_10__ {TYPE_1__ fcl_stat; } ;
typedef  TYPE_3__ fq_if_classq_t ;
struct TYPE_11__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; int /*<<< orphan*/  sc; } ;
typedef  TYPE_4__ cqrq_stat_sc_t ;

/* Variables and functions */
 size_t fq_if_service_to_priority (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
fq_if_stat_sc(fq_if_t *fqs, cqrq_stat_sc_t *stat)
{
	u_int32_t pri;
	fq_if_classq_t *fq_cl;

	if (stat == NULL)
		return;

	pri = fq_if_service_to_priority(fqs, stat->sc);
	fq_cl = &fqs->fqs_classq[pri];
	stat->packets = fq_cl->fcl_stat.fcl_pkt_cnt;
	stat->bytes = fq_cl->fcl_stat.fcl_byte_cnt;
}