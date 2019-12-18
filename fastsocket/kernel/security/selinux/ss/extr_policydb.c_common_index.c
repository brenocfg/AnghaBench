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
struct policydb {void** p_common_val_to_name; TYPE_1__ p_commons; } ;
struct common_datum {int value; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int common_index(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct common_datum *comdatum;

	comdatum = datum;
	p = datap;
	if (!comdatum->value || comdatum->value > p->p_commons.nprim)
		return -EINVAL;
	p->p_common_val_to_name[comdatum->value - 1] = key;
	return 0;
}