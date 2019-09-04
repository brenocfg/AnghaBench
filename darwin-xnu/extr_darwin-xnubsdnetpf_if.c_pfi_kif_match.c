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
struct pfi_kif {int dummy; } ;

/* Variables and functions */

int
pfi_kif_match(struct pfi_kif *rule_kif, struct pfi_kif *packet_kif)
{

	if (rule_kif == NULL || rule_kif == packet_kif)
		return (1);

	return (0);
}