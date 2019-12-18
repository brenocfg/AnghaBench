#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* kauth_cred_t ;
struct TYPE_5__ {int /*<<< orphan*/  cr_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLCRED_CHECK (TYPE_1__*) ; 
 int OSAddAtomicLong (int,long*) ; 
 int /*<<< orphan*/  get_backtrace () ; 
 scalar_t__ is_target_cred (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
kauth_cred_ref(kauth_cred_t cred)
{
	int		old_value;
	
	NULLCRED_CHECK(cred);

	old_value = OSAddAtomicLong(1, (long*)&cred->cr_ref);

	if (old_value < 1)
		panic("kauth_cred_ref: trying to take a reference on a cred with no references");

#if 0 // use this to watch a specific credential
	if ( is_target_cred( cred ) != 0 ) {
 		get_backtrace( );
	}
#endif
		
	return;
}