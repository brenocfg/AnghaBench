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
struct page {int dummy; } ;
struct mem_cgroup_per_zone {int dummy; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 struct mem_cgroup_per_zone* mem_cgroup_zoneinfo (struct mem_cgroup*,int,int) ; 
 int page_to_nid (struct page*) ; 
 int page_zonenum (struct page*) ; 

__attribute__((used)) static struct mem_cgroup_per_zone *
page_cgroup_zoneinfo(struct mem_cgroup *mem, struct page *page)
{
	int nid = page_to_nid(page);
	int zid = page_zonenum(page);

	return mem_cgroup_zoneinfo(mem, nid, zid);
}