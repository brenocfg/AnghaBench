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
struct work_struct {int dummy; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ o2net_accept_one (struct socket*) ; 
 struct socket* o2net_listen_sock ; 

__attribute__((used)) static void o2net_accept_many(struct work_struct *work)
{
	struct socket *sock = o2net_listen_sock;
	while (o2net_accept_one(sock) == 0)
		cond_resched();
}