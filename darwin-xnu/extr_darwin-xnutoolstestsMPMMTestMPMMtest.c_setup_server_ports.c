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
struct port_args {int req_size; int reply_size; int* set; int* port_list; int server_num; int rcv_set; int port; void* reply_msg; void* req_msg; } ;
typedef  int mach_port_t ;
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
 scalar_t__ bootstrap_register (int,char*,int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mach_error (char*,scalar_t__) ; 
 scalar_t__ mach_port_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mach_port_insert_member (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ mach_port_insert_right (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 void* malloc (int) ; 
 int num_ints ; 
 int portcount ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** server_port_name ; 
 int setcount ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stress_prepost ; 
 scalar_t__ task_get_bootstrap_port (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ useset ; 
 int verbose ; 

void setup_server_ports(struct port_args *ports)
{
	kern_return_t ret = 0;
	mach_port_t bsport;
	mach_port_t port;

	ports->req_size = MAX(sizeof(ipc_inline_message) +  
			sizeof(u_int32_t) * num_ints, 
			sizeof(ipc_complex_message));
	ports->reply_size = sizeof(ipc_trivial_message) - 
		sizeof(mach_msg_trailer_t);
	ports->req_msg = malloc(ports->req_size);
	ports->reply_msg = malloc(ports->reply_size);
	if (setcount > 0) {
		ports->set = (mach_port_t *)calloc(sizeof(mach_port_t), setcount);
		if (!ports->set) {
			fprintf(stderr, "calloc(%lu, %d) failed!\n", sizeof(mach_port_t), setcount);
			exit(1);
		}
	}
	if (stress_prepost) {
		ports->port_list = (mach_port_t *)calloc(sizeof(mach_port_t), portcount);
		if (!ports->port_list) {
			fprintf(stderr, "calloc(%lu, %d) failed!\n", sizeof(mach_port_t), portcount);
			exit(1);
		}
	}

	if (useset) {
		mach_port_t set;
		if (setcount < 1) {
			fprintf(stderr, "Can't use sets with a setcount of %d\n", setcount);
			exit(1);
		}

		for (int ns = 0; ns < setcount; ns++) {
			ret = mach_port_allocate(mach_task_self(),
						 MACH_PORT_RIGHT_PORT_SET,
						 &ports->set[ns]);
			if (KERN_SUCCESS != ret) {
				mach_error("mach_port_allocate(SET): ", ret);
				exit(1);
			}
			if (verbose > 1)
				printf("SVR[%d] allocated set[%d] %#x\n",
				       ports->server_num, ns, ports->set[ns]);

			set = ports->set[ns];
		}

		/* receive on a port set (always use the first in the chain) */
		ports->rcv_set = ports->set[0];
	}

	/* stuff the portset(s) with ports */
	for (int i = 0; i < portcount; i++) {
		ret = mach_port_allocate(mach_task_self(), 
					 MACH_PORT_RIGHT_RECEIVE,  
					 &port);
		if (KERN_SUCCESS != ret) {
			mach_error("mach_port_allocate(PORT): ", ret);
			exit(1);
		}

		if (stress_prepost)
			ports->port_list[i] = port;

		if (useset) {
			/* insert the port into _all_ allocated lowest-level sets */
			for (int ns = 0; ns < setcount; ns++) {
				if (verbose > 1)
					printf("SVR[%d] moving port %#x into set %#x...\n",
					       ports->server_num, port, ports->set[ns]);
				ret = mach_port_insert_member(mach_task_self(),
							      port, ports->set[ns]);
				if (KERN_SUCCESS != ret) {
					mach_error("mach_port_insert_member(): ", ret);
					exit(1);
				}
			}
		}
	}

	/* use the last one as the server's bootstrap port */
	ports->port = port;

	if (stress_prepost) {
		/* insert a send right for _each_ port */
		for (int i = 0; i < portcount; i++) {
			ret = mach_port_insert_right(mach_task_self(),
						     ports->port_list[i],
						     ports->port_list[i],
						     MACH_MSG_TYPE_MAKE_SEND);
			if (KERN_SUCCESS != ret) {
				mach_error("mach_port_insert_right(): ", ret);
				exit(1);
			}
		}
	} else {
		ret = mach_port_insert_right(mach_task_self(),
					     ports->port,
					     ports->port,
					     MACH_MSG_TYPE_MAKE_SEND);
		if (KERN_SUCCESS != ret) {
			mach_error("mach_port_insert_right(): ", ret);
			exit(1);
		}
	}

	ret = task_get_bootstrap_port(mach_task_self(), &bsport);
	if (KERN_SUCCESS != ret) {
		mach_error("task_get_bootstrap_port(): ", ret);
		exit(1);
	}

	if (verbose) {
		printf("server waiting for IPC messages from client on port '%s' (%#x).\n",
			server_port_name[ports->server_num], ports->port);
	}
	ret = bootstrap_register(bsport,
				 server_port_name[ports->server_num],
				 ports->port);
	if (KERN_SUCCESS != ret) {
		mach_error("bootstrap_register(): ", ret);
		exit(1);
	}
}