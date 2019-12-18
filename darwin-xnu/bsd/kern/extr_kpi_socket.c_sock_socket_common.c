#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* socket_t ;
typedef  int /*<<< orphan*/ * sock_upcall ;
typedef  int errno_t ;
struct TYPE_7__ {int /*<<< orphan*/  nas_socket_in_kernel_os_total; int /*<<< orphan*/  nas_socket_in_kernel_total; } ;
struct TYPE_6__ {scalar_t__ last_upid; scalar_t__ last_pid; int /*<<< orphan*/  so_flags1; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INC_ATOMIC_INT64_LIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOF1_IN_KERNEL_SOCKET ; 
 TYPE_5__ net_api_stats ; 
 int /*<<< orphan*/  sock_setupcall (TYPE_1__*,int /*<<< orphan*/ *,void*) ; 
 int socreate (int,TYPE_1__**,int,int) ; 

errno_t
sock_socket_common(int domain, int type, int protocol, sock_upcall callback,
    void *context, socket_t *new_so, bool is_internal)
{
	int error = 0;

	if (new_so == NULL)
		return (EINVAL);

	/* socreate will create an initial so_count */
	error = socreate(domain, new_so, type, protocol);
	if (error == 0) {
		/*
		 * This is an in-kernel socket
		 */
		(*new_so)->so_flags1 |= SOF1_IN_KERNEL_SOCKET;
		INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_in_kernel_total);
		if (is_internal) {
			INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_in_kernel_os_total);
		}

		/* see comments in sock_setupcall() */
		if (callback != NULL) {
			sock_setupcall(*new_so, callback, context);
		}
		/* 
		 * last_pid and last_upid should be zero for sockets
		 * created using sock_socket
		 */
		(*new_so)->last_pid = 0;
		(*new_so)->last_upid = 0;
	}
	return (error);
}