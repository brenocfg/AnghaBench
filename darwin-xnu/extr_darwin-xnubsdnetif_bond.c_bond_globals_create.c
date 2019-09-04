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
typedef  int /*<<< orphan*/ * lacp_system_ref ;
typedef  int /*<<< orphan*/  lacp_system_priority ;
typedef  TYPE_1__* bond_globals_ref ;
struct TYPE_4__ {int /*<<< orphan*/  system_priority; int /*<<< orphan*/  system; int /*<<< orphan*/  ifbond_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BOND ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* _MALLOC (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bond_globals_ref
bond_globals_create(lacp_system_priority sys_pri,
		    lacp_system_ref sys)
{
    bond_globals_ref	b;

    b = _MALLOC(sizeof(*b), M_BOND, M_WAITOK | M_ZERO);
    if (b == NULL) {
	return (NULL);
    }
    TAILQ_INIT(&b->ifbond_list);
    b->system = *sys;
    b->system_priority = sys_pri;
    return (b);
}