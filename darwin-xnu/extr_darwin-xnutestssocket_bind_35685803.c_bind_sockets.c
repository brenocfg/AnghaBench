#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int socket_count; int /*<<< orphan*/ * socket_list; scalar_t__ v6; } ;
typedef  TYPE_1__* SocketInfoRef ;

/* Variables and functions */
 int /*<<< orphan*/  T_LOG (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int sock_bind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_get_port (int /*<<< orphan*/ ) ; 
 int sockv6_bind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bind_sockets(SocketInfoRef info, const char * msg)
{
	for (int i = 0; i < info->socket_count; i++) {
		int		error;
		uint16_t	port;

		if (info->v6) {
			error = sockv6_bind(info->socket_list[i], 0);
		}
		else {
			error = sock_bind(info->socket_list[i], 0);
		}
		port = sock_get_port(info->socket_list[i]);
		if (debug) {
			T_LOG( "%s: fd %d port is %d error %d",
			       msg, info->socket_list[i], ntohs(port), error);
		}
	}
	return;
}