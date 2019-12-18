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
struct ib_mad_mgmt_vendor_class {int /*<<< orphan*/ * oui; } ;

/* Variables and functions */
 int MAX_MGMT_OUI ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int find_vendor_oui(struct ib_mad_mgmt_vendor_class *vendor_class,
			   char *oui)
{
	int i;

	for (i = 0; i < MAX_MGMT_OUI; i++)
		/* Is there matching OUI for this vendor class ? */
		if (!memcmp(vendor_class->oui[i], oui, 3))
			return i;

	return -1;
}