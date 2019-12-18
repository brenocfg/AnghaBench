#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum link_pm { ____Placeholder_link_pm } link_pm ;
struct TYPE_3__ {int value; char const* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* link_pm_policy ; 

__attribute__((used)) static const char *ata_scsi_lpm_get(enum link_pm policy)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(link_pm_policy); i++)
		if (link_pm_policy[i].value == policy)
			return link_pm_policy[i].name;

	return NULL;
}