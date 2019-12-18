#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nprim; } ;
struct policydb {struct class_datum** class_val_to_struct; void** p_class_val_to_name; TYPE_1__ p_classes; } ;
struct class_datum {int value; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int class_index(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct class_datum *cladatum;

	cladatum = datum;
	p = datap;
	if (!cladatum->value || cladatum->value > p->p_classes.nprim)
		return -EINVAL;
	p->p_class_val_to_name[cladatum->value - 1] = key;
	p->class_val_to_struct[cladatum->value - 1] = cladatum;
	return 0;
}