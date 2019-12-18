#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dc_tag; int /*<<< orphan*/ * dc_create; } ;
typedef  TYPE_1__ die_creator_t ;
typedef  scalar_t__ Dwarf_Half ;

/* Variables and functions */
 TYPE_1__* die_creators ; 

__attribute__((used)) static const die_creator_t *
die_tag2ctor(Dwarf_Half tag)
{
	const die_creator_t *dc;

	for (dc = die_creators; dc->dc_create != NULL; dc++) {
		if (dc->dc_tag == tag)
			return (dc);
	}

	return (NULL);
}