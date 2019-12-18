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

/* Variables and functions */
 int /*<<< orphan*/  nfsd_proc_fops ; 
 int /*<<< orphan*/  nfsd_svcstats ; 
 int /*<<< orphan*/  svc_proc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
nfsd_stat_init(void)
{
	svc_proc_register(&nfsd_svcstats, &nfsd_proc_fops);
}