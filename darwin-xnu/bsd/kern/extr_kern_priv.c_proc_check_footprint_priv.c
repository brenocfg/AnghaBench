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
 int /*<<< orphan*/  PRIV_VM_FOOTPRINT_LIMIT ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int priv_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
proc_check_footprint_priv(void) 
{
	return (priv_check_cred(kauth_cred_get(), PRIV_VM_FOOTPRINT_LIMIT, 0));
}