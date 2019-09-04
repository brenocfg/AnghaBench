#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* kauth_cred_t ;
struct TYPE_8__ {int cr_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SESSION_REF (TYPE_1__*) ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* kauth_cred_alloc () ; 

kauth_cred_t
kauth_cred_dup(kauth_cred_t cred)
{
	kauth_cred_t newcred;
#if CONFIG_MACF
	struct label *temp_label;
#endif
	
#if CRED_DIAGNOSTIC
	if (cred == NOCRED || cred == FSCRED)
		panic("kauth_cred_dup: bad credential");
#endif
	newcred = kauth_cred_alloc();
	if (newcred != NULL) {
#if CONFIG_MACF
		temp_label = newcred->cr_label;
#endif
		bcopy(cred, newcred, sizeof(*newcred));
#if CONFIG_MACF
		newcred->cr_label = temp_label;
		mac_cred_label_associate(cred, newcred);
#endif
		AUDIT_SESSION_REF(cred);
		newcred->cr_ref = 1;
	}
	return(newcred);
}