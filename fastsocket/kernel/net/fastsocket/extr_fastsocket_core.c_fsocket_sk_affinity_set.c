#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_1__* sk; } ;
struct TYPE_2__ {int sk_local; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SOCK_LOCAL ; 
 int /*<<< orphan*/  sock_set_flag (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsocket_sk_affinity_set(struct socket *sock, int cpu)
{
	sock_set_flag(sock->sk, SOCK_LOCAL);
	sock->sk->sk_local = cpu;

	DPRINTK(DEBUG, "Bind this listen socket to CPU %d", cpu);
}