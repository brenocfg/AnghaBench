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
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mac_cred_check_enforce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  priv_check ; 

int
mac_priv_check(kauth_cred_t cred, int priv)
{
	int error;

	if (!mac_cred_check_enforce(cred))
		return 0;

	MAC_CHECK(priv_check, cred, priv);

	return (error);
}