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
struct TYPE_2__ {int sv_nrpools; } ;

/* Variables and functions */
 TYPE_1__* nfsd_serv ; 

int nfsd_nrpools(void)
{
	if (nfsd_serv == NULL)
		return 0;
	else
		return nfsd_serv->sv_nrpools;
}