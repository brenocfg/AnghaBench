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
struct puser_nice_args {scalar_t__ who; int* errorp; int* foundp; int /*<<< orphan*/  prio; int /*<<< orphan*/  curp; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int PROC_RETURNED ; 
 int donice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
puser_donice_callback(proc_t p, void * arg)
{
	int error, n;
	struct puser_nice_args * pun = (struct puser_nice_args *)arg;
	kauth_cred_t my_cred;

	my_cred = kauth_cred_proc_ref(p);
	if (kauth_cred_getuid(my_cred) == pun->who) {
		error = donice(pun->curp, p, pun->prio);
		if (pun->errorp != NULL)
			*pun->errorp = error;
		if (pun->foundp != NULL) {
			n = *pun->foundp;
			*pun->foundp = n+1;
		}
	}
	kauth_cred_unref(&my_cred);

	return(PROC_RETURNED);
}