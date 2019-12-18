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
typedef  scalar_t__ u32 ;
struct pdi {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ PDI_END ; 
 scalar_t__ pdi_id (struct pdi const*) ; 
 size_t pdi_len (struct pdi const*) ; 

__attribute__((used)) static const struct pdi *
hermes_find_pdi(const struct pdi *first_pdi, u32 record_id, const void *end)
{
	const struct pdi *pdi = first_pdi;

	end -= sizeof(struct pdi);

	while (((void *) pdi <= end) &&
	       (pdi_id(pdi) != PDI_END)) {

		/* If the record ID matches, we are done */
		if (pdi_id(pdi) == record_id)
			return pdi;

		pdi = (struct pdi *) &pdi->data[pdi_len(pdi)];
	}
	return NULL;
}