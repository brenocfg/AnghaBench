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
struct sock {int dummy; } ;
struct ipv6_pinfo {struct ipv6_fl_socklist* ipv6_fl_list; } ;
struct ipv6_fl_socklist {int /*<<< orphan*/  fl; struct ipv6_fl_socklist* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  fl_release (int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree (struct ipv6_fl_socklist*) ; 

void fl6_free_socklist(struct sock *sk)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct ipv6_fl_socklist *sfl;

	while ((sfl = np->ipv6_fl_list) != NULL) {
		np->ipv6_fl_list = sfl->next;
		fl_release(sfl->fl);
		kfree(sfl);
	}
}