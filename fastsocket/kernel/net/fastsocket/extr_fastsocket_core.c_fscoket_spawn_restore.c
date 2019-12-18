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
struct TYPE_2__ {int /*<<< orphan*/  sk_local; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsocket_filp_close_spawn (int) ; 
 int /*<<< orphan*/  fsocket_process_affinity_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsocket_sk_affinity_release (struct socket*) ; 

void fscoket_spawn_restore(struct socket *sock, int fd)
{
	fsocket_sk_affinity_release(sock);
	fsocket_filp_close_spawn(fd);
	fsocket_process_affinity_restore(sock->sk->sk_local);
}