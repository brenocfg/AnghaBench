#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int uint64_t ;
struct TYPE_5__ {int int_hashlen; TYPE_2__* int_tail; TYPE_2__* int_head; int /*<<< orphan*/  int_nelems; TYPE_2__** int_hash; int /*<<< orphan*/  int_index; int /*<<< orphan*/  int_hdl; } ;
typedef  TYPE_1__ dt_inttab_t ;
struct TYPE_6__ {int inh_value; int inh_flags; int inh_index; struct TYPE_6__* inh_next; struct TYPE_6__* inh_hash; } ;
typedef  TYPE_2__ dt_inthash_t ;

/* Variables and functions */
 int DT_INT_SHARED ; 
 TYPE_2__* dt_alloc (int /*<<< orphan*/ ,int) ; 

int
dt_inttab_insert(dt_inttab_t *ip, uint64_t value, uint_t flags)
{
	uint_t h = value & (ip->int_hashlen - 1);
	dt_inthash_t *hp;

	if (flags & DT_INT_SHARED) {
		for (hp = ip->int_hash[h]; hp != NULL; hp = hp->inh_hash) {
			if (hp->inh_value == value && hp->inh_flags == flags)
				return (hp->inh_index);
		}
	}

	if ((hp = dt_alloc(ip->int_hdl, sizeof (dt_inthash_t))) == NULL)
		return (-1);

	hp->inh_hash = ip->int_hash[h];
	hp->inh_next = NULL;
	hp->inh_value = value;
	hp->inh_index = ip->int_index++;
	hp->inh_flags = flags;

	ip->int_hash[h] = hp;
	ip->int_nelems++;

	if (ip->int_head == NULL)
		ip->int_head = hp;
	else
		ip->int_tail->inh_next = hp;

	ip->int_tail = hp;
	return (hp->inh_index);
}