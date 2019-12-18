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
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET__GETOPT ; 
 int /*<<< orphan*/  current ; 
 int socket_has_perm (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_socket_getsockopt(struct socket *sock, int level,
				     int optname)
{
	return socket_has_perm(current, sock, SOCKET__GETOPT);
}