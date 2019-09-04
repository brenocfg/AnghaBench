#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ x86_pkg_t ;
struct TYPE_6__ {int /*<<< orphan*/  nPackages; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_decl (long*,int) ; 
 TYPE_1__* free_pkgs ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ topoParms ; 
 int /*<<< orphan*/  x86_topo_lock ; 

__attribute__((used)) static void
x86_package_free(x86_pkg_t *pkg)
{
    mp_safe_spin_lock(&x86_topo_lock);
    pkg->next = free_pkgs;
    free_pkgs = pkg;
    atomic_decl((long *) &topoParms.nPackages, 1);
    simple_unlock(&x86_topo_lock);
}