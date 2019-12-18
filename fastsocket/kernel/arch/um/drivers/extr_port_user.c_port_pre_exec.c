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
struct port_pre_exec_data {int /*<<< orphan*/  pipe_fd; int /*<<< orphan*/  sock_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RD ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port_pre_exec(void *arg)
{
	struct port_pre_exec_data *data = arg;

	dup2(data->sock_fd, 0);
	dup2(data->sock_fd, 1);
	dup2(data->sock_fd, 2);
	close(data->sock_fd);
	dup2(data->pipe_fd, 3);
	shutdown(3, SHUT_RD);
	close(data->pipe_fd);
}