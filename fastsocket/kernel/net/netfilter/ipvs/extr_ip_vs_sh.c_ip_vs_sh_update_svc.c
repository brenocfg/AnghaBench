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
struct ip_vs_sh_bucket {int dummy; } ;
struct ip_vs_service {struct ip_vs_sh_bucket* sched_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_sh_assign (struct ip_vs_sh_bucket*,struct ip_vs_service*) ; 
 int /*<<< orphan*/  ip_vs_sh_flush (struct ip_vs_sh_bucket*) ; 

__attribute__((used)) static int ip_vs_sh_update_svc(struct ip_vs_service *svc)
{
	struct ip_vs_sh_bucket *tbl = svc->sched_data;

	/* got to clean up hash buckets here */
	ip_vs_sh_flush(tbl);

	/* assign the hash buckets with the updated service */
	ip_vs_sh_assign(tbl, svc);

	return 0;
}