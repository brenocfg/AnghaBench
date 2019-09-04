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
struct port_args {int req_size; int reply_size; size_t server_num; int /*<<< orphan*/  port; void* reply_msg; void* req_msg; } ;
typedef  int /*<<< orphan*/  mach_msg_trailer_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_trivial_message ;
typedef  int /*<<< orphan*/  ipc_inline_message ;
typedef  int /*<<< orphan*/  ipc_complex_message ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_RECEIVE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  mach_error (char*,scalar_t__) ; 
 scalar_t__ mach_port_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 void* malloc (int) ; 
 int msg_type ; 
#define  msg_type_complex 130 
#define  msg_type_inline 129 
#define  msg_type_trivial 128 
 int num_ints ; 
 int num_msgs ; 
 scalar_t__ oneway ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*,char*) ; 
 char** server_port_name ; 
 scalar_t__ verbose ; 

void setup_client_ports(struct port_args *ports)
{
	kern_return_t ret = 0;
	switch(msg_type) {
		case msg_type_trivial:
			ports->req_size = sizeof(ipc_trivial_message);
			break;
		case msg_type_inline:
			ports->req_size = sizeof(ipc_inline_message) +  
				sizeof(u_int32_t) * num_ints;
			break;
		case msg_type_complex:
			ports->req_size = sizeof(ipc_complex_message);
			break;
	}
	ports->req_size -= sizeof(mach_msg_trailer_t);
	ports->reply_size = sizeof(ipc_trivial_message);
	ports->req_msg = malloc(ports->req_size);
	ports->reply_msg = malloc(ports->reply_size);

	ret = mach_port_allocate(mach_task_self(), 
			MACH_PORT_RIGHT_RECEIVE,  
			&(ports->port));
	if (KERN_SUCCESS != ret) {
		mach_error("mach_port_allocate(): ", ret);
		exit(1);
	}
	if (verbose) {
		printf("Client sending %d %s IPC messages to port '%s' in %s mode\n",
				num_msgs, (msg_type == msg_type_inline) ? 
				"inline" :  ((msg_type == msg_type_complex) ? 
					"complex" : "trivial"),  
				server_port_name[ports->server_num],
				(oneway ? "oneway" : "rpc"));
	}
}