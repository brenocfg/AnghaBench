#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * posix_cred_t ;
typedef  TYPE_1__* kauth_cred_t ;
struct TYPE_3__ {int /*<<< orphan*/  cr_posix; } ;

/* Variables and functions */

void
posix_cred_label(kauth_cred_t cred, posix_cred_t pcred)
{
	cred->cr_posix = *pcred;	/* structure assign for now */
}