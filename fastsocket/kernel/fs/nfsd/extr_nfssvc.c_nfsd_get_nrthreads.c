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
struct TYPE_4__ {int sv_nrpools; TYPE_1__* sv_pools; } ;
struct TYPE_3__ {int sp_nrthreads; } ;

/* Variables and functions */
 TYPE_2__* nfsd_serv ; 

int nfsd_get_nrthreads(int n, int *nthreads)
{
	int i = 0;

	if (nfsd_serv != NULL) {
		for (i = 0; i < nfsd_serv->sv_nrpools && i < n; i++)
			nthreads[i] = nfsd_serv->sv_pools[i].sp_nrthreads;
	}

	return 0;
}