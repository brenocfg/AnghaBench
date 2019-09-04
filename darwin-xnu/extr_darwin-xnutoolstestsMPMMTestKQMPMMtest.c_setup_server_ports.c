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
typedef  int /*<<< orphan*/  u_int32_t ;
struct port_args {int req_size; int reply_size; size_t server_num; int /*<<< orphan*/  port; int /*<<< orphan*/  pset; void* reply_msg; void* req_msg; } ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  mach_msg_trailer_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_trivial_message ;
typedef  int /*<<< orphan*/  ipc_inline_message ;
typedef  int /*<<< orphan*/  ipc_complex_message ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_MAKE_SEND ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_PORT_SET ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_RECEIVE ; 
 int MAX (int,int) ; 
 scalar_t__ bootstrap_register (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  mach_error (char*,scalar_t__) ; 
 scalar_t__ mach_port_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mach_port_insert_member (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mach_port_insert_right (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 void* malloc (int) ; 
 int num_ints ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char** server_port_name ; 
 scalar_t__ task_get_bootstrap_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ verbose ; 

void setup_server_ports(struct port_args *ports)
{
	kern_return_t ret = 0;
	mach_port_t bsport;

	ports->req_size = MAX(sizeof(ipc_inline_message) +  
			sizeof(u_int32_t) * num_ints, 
			sizeof(ipc_complex_message));
	ports->reply_size = sizeof(ipc_trivial_message) - 
		sizeof(mach_msg_trailer_t);
	ports->req_msg = malloc(ports->req_size);
	ports->reply_msg = malloc(ports->reply_size);

	ret = mach_port_allocate(mach_task_self(), 
			MACH_PORT_RIGHT_RECEIVE,  
			&(ports->port));
	if (KERN_SUCCESS != ret) {
		mach_error("mach_port_allocate(): ", ret);
		exit(1);
	}

	ret = mach_port_allocate(mach_task_self(), 
			MACH_PORT_RIGHT_PORT_SET,  
			&(ports->pset));
	if (KERN_SUCCESS != ret) {
		mach_error("mach_port_allocate(): ", ret);
		exit(1);
	}
	
	ret = mach_port_insert_member(mach_task_self(),
			ports->port,
			ports->pset);
	if (KERN_SUCCESS != ret) {
		mach_error("mach_port_insert_member(): ", ret);
		exit(1);
	}

	ret = mach_port_insert_right(mach_task_self(), 
			ports->port, 
			ports->port, 
			MACH_MSG_TYPE_MAKE_SEND);
	if (KERN_SUCCESS != ret) {
		mach_error("mach_port_insert_right(): ", ret);
		exit(1);
	}

	ret = task_get_bootstrap_port(mach_task_self(), &bsport);
	if (KERN_SUCCESS != ret) {
		mach_error("task_get_bootstrap_port(): ", ret);
		exit(1);
	}

	if (verbose) {
		printf("server waiting for IPC messages from client on port '%s'.\n",
			server_port_name[ports->server_num]);
	}
	ret = bootstrap_register(bsport,
				 server_port_name[ports->server_num],
				 ports->port);
	if (KERN_SUCCESS != ret) {
		mach_error("bootstrap_register(): ", ret);
		exit(1);
	}
}