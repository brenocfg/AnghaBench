#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nprim; } ;
struct policydb {void** p_sens_val_to_name; TYPE_2__ p_levels; } ;
struct level_datum {TYPE_1__* level; int /*<<< orphan*/  isalias; } ;
struct TYPE_3__ {int sens; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int sens_index(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct level_datum *levdatum;

	levdatum = datum;
	p = datap;

	if (!levdatum->isalias) {
		if (!levdatum->level->sens ||
		    levdatum->level->sens > p->p_levels.nprim)
			return -EINVAL;
		p->p_sens_val_to_name[levdatum->level->sens - 1] = key;
	}

	return 0;
}