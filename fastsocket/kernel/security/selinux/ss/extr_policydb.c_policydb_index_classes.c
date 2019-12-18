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
struct TYPE_4__ {int nprim; int /*<<< orphan*/  table; } ;
struct TYPE_3__ {int nprim; int /*<<< orphan*/  table; } ;
struct policydb {TYPE_2__ p_classes; void* p_class_val_to_name; void* class_val_to_struct; TYPE_1__ p_commons; void* p_common_val_to_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  class_index ; 
 int /*<<< orphan*/  common_index ; 
 int hashtab_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct policydb*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int policydb_index_classes(struct policydb *p)
{
	int rc;

	p->p_common_val_to_name =
		kmalloc(p->p_commons.nprim * sizeof(char *), GFP_KERNEL);
	if (!p->p_common_val_to_name) {
		rc = -ENOMEM;
		goto out;
	}

	rc = hashtab_map(p->p_commons.table, common_index, p);
	if (rc)
		goto out;

	p->class_val_to_struct =
		kmalloc(p->p_classes.nprim * sizeof(*(p->class_val_to_struct)), GFP_KERNEL);
	if (!p->class_val_to_struct) {
		rc = -ENOMEM;
		goto out;
	}

	p->p_class_val_to_name =
		kmalloc(p->p_classes.nprim * sizeof(char *), GFP_KERNEL);
	if (!p->p_class_val_to_name) {
		rc = -ENOMEM;
		goto out;
	}

	rc = hashtab_map(p->p_classes.table, class_index, p);
out:
	return rc;
}