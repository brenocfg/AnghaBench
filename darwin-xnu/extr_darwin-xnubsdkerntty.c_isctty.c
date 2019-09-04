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
struct tty {struct session* t_session; } ;
struct session {int dummy; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_4__ {int p_flag; } ;

/* Variables and functions */
 int P_CONTROLT ; 
 struct session* proc_session (TYPE_1__*) ; 
 int /*<<< orphan*/  session_rele (struct session*) ; 

__attribute__((used)) static int 
isctty(proc_t p, struct tty  *tp)
{
	int retval;
	struct session * sessp;

	sessp = proc_session(p);
	retval = (sessp == tp->t_session && p->p_flag & P_CONTROLT);
	session_rele(sessp);
	return(retval);
}