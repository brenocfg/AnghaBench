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
struct sockaddr_un {int dummy; } ;
struct sock {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct sock* __unix_find_socket_byname (struct net*,struct sockaddr_un*,int,int,unsigned int) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unix_table_lock ; 

__attribute__((used)) static inline struct sock *unix_find_socket_byname(struct net *net,
						   struct sockaddr_un *sunname,
						   int len, int type,
						   unsigned hash)
{
	struct sock *s;

	spin_lock(&unix_table_lock);
	s = __unix_find_socket_byname(net, sunname, len, type, hash);
	if (s)
		sock_hold(s);
	spin_unlock(&unix_table_lock);
	return s;
}