#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct proc {int dummy; } ;
struct mac {int /*<<< orphan*/  m_buflen; int /*<<< orphan*/  m_string; } ;
typedef  TYPE_1__* kauth_cred_t ;
struct TYPE_4__ {int /*<<< orphan*/  cr_label; } ;

/* Variables and functions */
 int MAC_EXTERNALIZE_AUDIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cred ; 
 TYPE_1__* kauth_cred_proc_ref (struct proc*) ; 
 int /*<<< orphan*/  kauth_cred_unref (TYPE_1__**) ; 

int
mac_cred_label_externalize_audit(struct proc *p, struct mac *mac)
{
	kauth_cred_t cr;
	int error;

	cr = kauth_cred_proc_ref(p);

	error = MAC_EXTERNALIZE_AUDIT(cred, cr->cr_label,
	    mac->m_string, mac->m_buflen);

	kauth_cred_unref(&cr);
	return (error);
}