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
struct iova_domain {int dummy; } ;
struct iova {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_iova (struct iova_domain*,struct iova*) ; 
 struct iova* find_iova (struct iova_domain*,unsigned long) ; 

void
free_iova(struct iova_domain *iovad, unsigned long pfn)
{
	struct iova *iova = find_iova(iovad, pfn);
	if (iova)
		__free_iova(iovad, iova);

}