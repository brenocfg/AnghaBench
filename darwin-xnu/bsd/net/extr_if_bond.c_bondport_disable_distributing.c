#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ifbond_ref ;
typedef  TYPE_2__* bondport_ref ;
struct TYPE_10__ {scalar_t__ verbose; } ;
struct TYPE_9__ {TYPE_1__* po_bond; } ;
struct TYPE_8__ {int ifb_distributing_count; TYPE_2__** ifb_distributing_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  bondport_flags_clear_distributing (TYPE_2__*) ; 
 scalar_t__ bondport_flags_distributing (TYPE_2__*) ; 
 int /*<<< orphan*/  bondport_get_name (TYPE_2__*) ; 
 TYPE_3__* g_bond ; 
 int /*<<< orphan*/  timestamp_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bondport_disable_distributing(bondport_ref p)
{
    if (bondport_flags_distributing(p)) {
	bondport_ref *	array;
	ifbond_ref	bond;
	int		count;
	int		i;

	bond = p->po_bond;
	array = bond->ifb_distributing_array;
	count = bond->ifb_distributing_count;
	for (i = 0; i < count; i++) {
	    if (array[i] == p) {
		int	j;

		for (j = i; j < (count - 1); j++) {
		    array[j] = array[j + 1];
		}
		break;
	    }
	}
	bond->ifb_distributing_count--;
	if (g_bond->verbose) {
	    timestamp_printf("[%s] Distribution Disabled\n",
			     bondport_get_name(p));
	}
	bondport_flags_clear_distributing(p);
    }
    return;
}