#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t dtrd_offset; int /*<<< orphan*/  dtrd_size; } ;
typedef  TYPE_1__ dtrace_recdesc_t ;
struct TYPE_14__ {TYPE_5__* dtah_all; } ;
struct TYPE_15__ {int dtat_maxcpu; TYPE_6__ dtat_hash; } ;
struct TYPE_10__ {TYPE_7__ dt_aggregate; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_11__ {int dtagd_nrecs; TYPE_1__* dtagd_rec; } ;
typedef  TYPE_3__ dtrace_aggdesc_t ;
struct TYPE_12__ {int /*<<< orphan*/ ** dtada_percpu; int /*<<< orphan*/ * dtada_data; TYPE_3__* dtada_desc; } ;
typedef  TYPE_4__ dtrace_aggdata_t ;
struct TYPE_13__ {TYPE_4__ dtahe_data; struct TYPE_13__* dtahe_nextall; } ;
typedef  TYPE_5__ dt_ahashent_t ;
typedef  TYPE_6__ dt_ahash_t ;
typedef  TYPE_7__ dt_aggregate_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
dtrace_aggregate_clear(dtrace_hdl_t *dtp)
{
	dt_aggregate_t *agp = &dtp->dt_aggregate;
	dt_ahash_t *hash = &agp->dtat_hash;
	dt_ahashent_t *h;
	dtrace_aggdata_t *data;
	dtrace_aggdesc_t *aggdesc;
	dtrace_recdesc_t *rec;
	int i, max_cpus = agp->dtat_maxcpu;

	for (h = hash->dtah_all; h != NULL; h = h->dtahe_nextall) {
		aggdesc = h->dtahe_data.dtada_desc;
		rec = &aggdesc->dtagd_rec[aggdesc->dtagd_nrecs - 1];
		data = &h->dtahe_data;

		bzero(&data->dtada_data[rec->dtrd_offset], rec->dtrd_size);

		if (data->dtada_percpu == NULL)
			continue;

		for (i = 0; i < max_cpus; i++)
			bzero(data->dtada_percpu[i], rec->dtrd_size);
	}
}