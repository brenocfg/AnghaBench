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

/* Variables and functions */
 int if_clone_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_cloner ; 
 int /*<<< orphan*/  vlan_lock_init () ; 

__attribute__((used)) static int
vlan_clone_attach(void)
{
    int error;

    error = if_clone_attach(&vlan_cloner);
    if (error != 0)
        return error;
    vlan_lock_init();
    return 0;
}