#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlan_globals_ref ;
struct TYPE_5__ {scalar_t__ verbose; int /*<<< orphan*/  parent_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_VLAN ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  _FREE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* _MALLOC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_vlan ; 
 int /*<<< orphan*/  vlan_assert_lock_not_held () ; 
 int /*<<< orphan*/  vlan_lock () ; 
 int /*<<< orphan*/  vlan_unlock () ; 

__attribute__((used)) static int
vlan_globals_init(void)
{
    vlan_globals_ref	v;

    vlan_assert_lock_not_held();

    if (g_vlan != NULL) {
	return (0);
    }
    v = _MALLOC(sizeof(*v), M_VLAN, M_WAITOK);
    if (v != NULL) {
	LIST_INIT(&v->parent_list);
	v->verbose = 0;
    }
    vlan_lock();
    if (g_vlan != NULL) {
	vlan_unlock();
	if (v != NULL) {
	    _FREE(v, M_VLAN);
	}
	return (0);
    }
    g_vlan = v;
    vlan_unlock();
    if (v == NULL) {
	return (ENOMEM);
    }
    return (0);
}