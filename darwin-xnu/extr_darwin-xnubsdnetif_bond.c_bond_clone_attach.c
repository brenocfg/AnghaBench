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
 int /*<<< orphan*/  bond_cloner ; 
 int /*<<< orphan*/  bond_lock_init () ; 
 int if_clone_attach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bond_clone_attach(void)
{
    int error;

    if ((error = if_clone_attach(&bond_cloner)) != 0)
	return error;
    bond_lock_init();
    return 0;
}