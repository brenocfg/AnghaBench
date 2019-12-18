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
typedef  TYPE_1__* uthread_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_2__ {int /*<<< orphan*/  uu_ucred; } ;

/* Variables and functions */
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 

void
uthread_cred_free(void *uthread)
{
	uthread_t uth = (uthread_t)uthread;

	/* and free the uthread itself */
	if (IS_VALID_CRED(uth->uu_ucred)) {
		kauth_cred_t oldcred = uth->uu_ucred;
		uth->uu_ucred = NOCRED;
		kauth_cred_unref(&oldcred);
	}
}