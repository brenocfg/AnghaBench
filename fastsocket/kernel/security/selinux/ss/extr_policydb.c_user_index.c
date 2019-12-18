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
struct user_datum {int value; scalar_t__ bounds; } ;
struct TYPE_2__ {int nprim; } ;
struct policydb {struct user_datum** user_val_to_struct; void** p_user_val_to_name; TYPE_1__ p_users; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int user_index(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct user_datum *usrdatum;

	usrdatum = datum;
	p = datap;
	if (!usrdatum->value
	    || usrdatum->value > p->p_users.nprim
	    || usrdatum->bounds > p->p_users.nprim)
		return -EINVAL;
	p->p_user_val_to_name[usrdatum->value - 1] = key;
	p->user_val_to_struct[usrdatum->value - 1] = usrdatum;
	return 0;
}