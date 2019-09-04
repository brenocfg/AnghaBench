#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_2__ {int /*<<< orphan*/  cr_rgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLCRED_CHECK (int /*<<< orphan*/ ) ; 
 TYPE_1__* posix_cred_get (int /*<<< orphan*/ ) ; 

gid_t
kauth_cred_getrgid(kauth_cred_t cred)
{
	NULLCRED_CHECK(cred);
	return(posix_cred_get(cred)->cr_rgid);
}