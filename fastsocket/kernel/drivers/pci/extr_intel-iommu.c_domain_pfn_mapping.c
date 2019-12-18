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
struct dmar_domain {int dummy; } ;

/* Variables and functions */
 int __domain_mapping (struct dmar_domain*,unsigned long,int /*<<< orphan*/ *,unsigned long,unsigned long,int) ; 

__attribute__((used)) static inline int domain_pfn_mapping(struct dmar_domain *domain, unsigned long iov_pfn,
				     unsigned long phys_pfn, unsigned long nr_pages,
				     int prot)
{
	return __domain_mapping(domain, iov_pfn, NULL, phys_pfn, nr_pages, prot);
}