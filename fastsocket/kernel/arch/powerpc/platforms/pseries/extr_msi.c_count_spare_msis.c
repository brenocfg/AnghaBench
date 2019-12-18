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
typedef  int u32 ;
struct msi_counts {int request; int quota; int /*<<< orphan*/  over_quota; int /*<<< orphan*/  spare; struct device_node* requestor; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int max (int,int) ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *count_spare_msis(struct device_node *dn, void *data)
{
	struct msi_counts *counts = data;
	const u32 *p;
	int req;

	if (dn == counts->requestor)
		req = counts->request;
	else {
		/* We don't know if a driver will try to use MSI or MSI-X,
		 * so we just have to punt and use the larger of the two. */
		req = 0;
		p = of_get_property(dn, "ibm,req#msi", NULL);
		if (p)
			req = *p;

		p = of_get_property(dn, "ibm,req#msi-x", NULL);
		if (p)
			req = max(req, (int)*p);
	}

	if (req < counts->quota)
		counts->spare += counts->quota - req;
	else if (req > counts->quota)
		counts->over_quota++;

	return NULL;
}