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
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 

int
kauth_cred_issuser(kauth_cred_t cred)
{
	return(kauth_cred_getuid(cred) == 0);
}