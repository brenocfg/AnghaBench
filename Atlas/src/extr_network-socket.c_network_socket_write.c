#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network_socket_retval_t ;
struct TYPE_5__ {scalar_t__ socket_type; } ;
typedef  TYPE_1__ network_socket ;

/* Variables and functions */
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  network_socket_write_send (TYPE_1__*,int) ; 
 int /*<<< orphan*/  network_socket_write_writev (TYPE_1__*,int) ; 

network_socket_retval_t network_socket_write(network_socket *con, int send_chunks) {
	if (con->socket_type == SOCK_STREAM) {
#ifdef HAVE_WRITEV
		return network_socket_write_writev(con, send_chunks);
#else
		return network_socket_write_send(con, send_chunks);
#endif
	} else {
		return network_socket_write_send(con, send_chunks);
	}
}