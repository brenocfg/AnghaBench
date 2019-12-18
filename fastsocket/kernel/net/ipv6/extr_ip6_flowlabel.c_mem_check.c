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
struct ipv6_fl_socklist {struct ipv6_fl_socklist* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int ENOBUFS ; 
 int FL_MAX_PER_SOCK ; 
 int FL_MAX_SIZE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fl_size ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 

__attribute__((used)) static int mem_check(struct sock *sk)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct ipv6_fl_socklist *sfl;
	int room = FL_MAX_SIZE - atomic_read(&fl_size);
	int count = 0;

	if (room > FL_MAX_SIZE - FL_MAX_PER_SOCK)
		return 0;

	for (sfl = np->ipv6_fl_list; sfl; sfl = sfl->next)
		count++;

	if (room <= 0 ||
	    ((count >= FL_MAX_PER_SOCK ||
	     (count > 0 && room < FL_MAX_SIZE/2) || room < FL_MAX_SIZE/4)
	     && !capable(CAP_NET_ADMIN)))
		return -ENOBUFS;

	return 0;
}