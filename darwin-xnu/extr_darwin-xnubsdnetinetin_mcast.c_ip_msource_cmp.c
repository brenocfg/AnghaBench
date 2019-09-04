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
struct ip_msource {scalar_t__ ims_haddr; } ;

/* Variables and functions */

__attribute__((used)) static __inline int
ip_msource_cmp(const struct ip_msource *a, const struct ip_msource *b)
{

	if (a->ims_haddr < b->ims_haddr)
		return (-1);
	if (a->ims_haddr == b->ims_haddr)
		return (0);
	return (1);
}