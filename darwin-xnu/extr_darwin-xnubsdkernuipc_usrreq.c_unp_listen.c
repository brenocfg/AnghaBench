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
struct unpcb {int /*<<< orphan*/  unp_flags; int /*<<< orphan*/  unp_peercred; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNP_HAVEPCCACHED ; 
 int /*<<< orphan*/  cru2x (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
unp_listen(struct unpcb *unp, proc_t p)
{
	kauth_cred_t safecred = kauth_cred_proc_ref(p);
	cru2x(safecred, &unp->unp_peercred);
	kauth_cred_unref(&safecred);
	unp->unp_flags |= UNP_HAVEPCCACHED;
	return (0);
}