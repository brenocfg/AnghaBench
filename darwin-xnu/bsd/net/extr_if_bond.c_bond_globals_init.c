#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  lacp_system_ref ;
typedef  int /*<<< orphan*/  ifname ;
typedef  int /*<<< orphan*/ * bond_globals_ref ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 scalar_t__ IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  M_BOND ; 
 int /*<<< orphan*/  _FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_assert_lock_not_held () ; 
 int /*<<< orphan*/ * bond_globals_create (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_lock () ; 
 int /*<<< orphan*/  bond_unlock () ; 
 int /*<<< orphan*/ * g_bond ; 
 struct ifnet* ifunit (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
bond_globals_init(void)
{
    bond_globals_ref	b;
    int			i;
    struct ifnet * 	ifp;

    bond_assert_lock_not_held();

    if (g_bond != NULL) {
	return (0);
    }

    /*
     * use en0's ethernet address as the system identifier, and if it's not
     * there, use en1 .. en3
     */
    ifp = NULL;
    for (i = 0; i < 4; i++) {
	char 		ifname[IFNAMSIZ+1];
	snprintf(ifname, sizeof(ifname), "en%d", i);
	ifp = ifunit(ifname);
	if (ifp != NULL) {
	    break;
	}
    }
    b = NULL;
    if (ifp != NULL) {
	b = bond_globals_create(0x8000, (lacp_system_ref)IF_LLADDR(ifp));
    }
    bond_lock();
    if (g_bond != NULL) {
	bond_unlock();
	_FREE(b, M_BOND);
	return (0);
    }
    g_bond = b;
    bond_unlock();
    if (ifp == NULL) {
	return (ENXIO);
    }
    if (b == NULL) {
	return (ENOMEM);
    }
    return (0);
}