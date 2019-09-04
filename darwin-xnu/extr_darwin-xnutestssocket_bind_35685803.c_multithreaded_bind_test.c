#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_4__ {int v6; int socket_count; int* socket_list; } ;
typedef  TYPE_1__ SocketInfo ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_ZERO (int,char*,...) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  bind_sockets (TYPE_1__*,char*) ; 
 int close (int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  second_thread ; 
 int sock_open (int /*<<< orphan*/ ) ; 
 int sockv6_open (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
multithreaded_bind_test(bool v6, int socket_count)
{
	int		error;
	SocketInfo	info;
	int 	socket_list[socket_count];
	pthread_t 	thread;

	info.v6 = v6;
	for (int i = 0; i < socket_count; i++) {
		if (v6) {
			socket_list[i] = sockv6_open(SOCK_STREAM);
		} else {
			socket_list[i] = sock_open(SOCK_STREAM);
		}
	}
	info.socket_count = socket_count;
	info.socket_list = socket_list;
	error = pthread_create(&thread, NULL, second_thread, &info);
	T_QUIET;
	T_ASSERT_POSIX_ZERO(error, "pthread_create");

	/* compete with second thread */
	bind_sockets(&info, "main");
	error = pthread_join(thread, NULL);
	T_QUIET;
	T_ASSERT_POSIX_ZERO(error, "pthread_join");

	for (int i = 0; i < socket_count; i++) {
		error =	close(socket_list[i]);
		T_QUIET;
		T_ASSERT_POSIX_ZERO(error, "close socket %d", socket_list[i]);
	}
}