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
typedef  int /*<<< orphan*/  socket_t ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ SOCK_DOM (int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ SOCK_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tcp_stream_priority (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
sock_set_tcp_stream_priority(socket_t sock)
{
	if ((SOCK_DOM(sock) == PF_INET || SOCK_DOM(sock) == PF_INET6) &&
	    SOCK_TYPE(sock) == SOCK_STREAM) {
		set_tcp_stream_priority(sock);
	}
}