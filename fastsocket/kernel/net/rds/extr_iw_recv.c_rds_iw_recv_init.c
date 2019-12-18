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
struct sysinfo {int totalram; } ;
struct rds_page_frag {int dummy; } ;
struct rds_iw_incoming {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int RDS_FRAG_SIZE ; 
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (void*) ; 
 void* rds_iw_frag_slab ; 
 void* rds_iw_incoming_slab ; 
 int rds_iw_sysctl_max_recv_allocation ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 

int rds_iw_recv_init(void)
{
	struct sysinfo si;
	int ret = -ENOMEM;

	/* Default to 30% of all available RAM for recv memory */
	si_meminfo(&si);
	rds_iw_sysctl_max_recv_allocation = si.totalram / 3 * PAGE_SIZE / RDS_FRAG_SIZE;

	rds_iw_incoming_slab = kmem_cache_create("rds_iw_incoming",
					sizeof(struct rds_iw_incoming),
					0, 0, NULL);
	if (!rds_iw_incoming_slab)
		goto out;

	rds_iw_frag_slab = kmem_cache_create("rds_iw_frag",
					sizeof(struct rds_page_frag),
					0, 0, NULL);
	if (!rds_iw_frag_slab)
		kmem_cache_destroy(rds_iw_incoming_slab);
	else
		ret = 0;
out:
	return ret;
}