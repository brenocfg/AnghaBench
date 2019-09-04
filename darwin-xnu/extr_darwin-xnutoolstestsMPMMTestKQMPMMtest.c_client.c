#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct port_args {int server_num; int /*<<< orphan*/  port; int /*<<< orphan*/  reply_size; TYPE_3__* reply_msg; int /*<<< orphan*/  req_size; TYPE_3__* req_msg; } ;
typedef  int /*<<< orphan*/  mach_port_t ;
struct TYPE_8__ {int msgh_id; int /*<<< orphan*/  msgh_local_port; int /*<<< orphan*/  msgh_size; scalar_t__ msgh_bits; int /*<<< orphan*/  msgh_remote_port; } ;
typedef  TYPE_3__ mach_msg_header_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_7__ {int size; int /*<<< orphan*/  type; int /*<<< orphan*/  copy; int /*<<< orphan*/  deallocate; void* address; } ;
struct TYPE_6__ {int msgh_descriptor_count; } ;
struct TYPE_9__ {TYPE_2__ descriptor; TYPE_1__ body; } ;
typedef  TYPE_4__ ipc_complex_message ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MACH_MSGH_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MACH_MSGH_BITS_COMPLEX ; 
 int /*<<< orphan*/  MACH_MSG_OOL_DESCRIPTOR ; 
 scalar_t__ MACH_MSG_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TIMEOUT_NONE ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_COPY_SEND ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_MAKE_SEND ; 
 int /*<<< orphan*/  MACH_MSG_VIRTUAL_COPY ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int MACH_RCV_INTERRUPT ; 
 int MACH_RCV_MSG ; 
 int MACH_SEND_MSG ; 
 int PAGE_SIZE ; 
 scalar_t__ bootstrap_look_up (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 long* client_memory ; 
 int client_pages ; 
 int /*<<< orphan*/  client_work () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  mach_error (char*,scalar_t__) ; 
 scalar_t__ mach_msg (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 void* malloc (int) ; 
 scalar_t__ msg_type ; 
 scalar_t__ msg_type_complex ; 
 int num_ints ; 
 int num_msgs ; 
 scalar_t__ oneway ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 char** server_port_name ; 
 int /*<<< orphan*/  setup_client_ports (struct port_args*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ task_get_bootstrap_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_setup (int) ; 
 scalar_t__ verbose ; 

void *client(void *threadarg) 
{
	struct port_args args;
	int idx;
	mach_msg_header_t *req, *reply; 
	mach_port_t bsport, servport;
	kern_return_t ret;
	int server_num = (int) threadarg;
	void *ints = malloc(sizeof(u_int32_t) * num_ints);

	if (verbose) 
		printf("client(%d) started, server port name %s\n",
			server_num, server_port_name[server_num]);

	args.server_num = server_num;
	thread_setup(server_num + 1);

	/* find server port */
	ret = task_get_bootstrap_port(mach_task_self(), &bsport);
	if (KERN_SUCCESS != ret) {
		mach_error("task_get_bootstrap_port(): ", ret);
		exit(1);
	}
	ret = bootstrap_look_up(bsport,
				server_port_name[server_num],
				&servport); 
	if (KERN_SUCCESS != ret) {
		mach_error("bootstrap_look_up(): ", ret);
		exit(1);
	}

	setup_client_ports(&args);

	/* Allocate and touch memory */
	if (client_pages) {
		unsigned	i;
		client_memory = (long *) malloc(client_pages * PAGE_SIZE);
		for (i = 0; i < client_pages; i++)
			client_memory[i * PAGE_SIZE / sizeof(long)] = 0;
	}
	
	/* start message loop */
	for (idx = 0; idx < num_msgs; idx++) {
		req = args.req_msg;
		reply = args.reply_msg;

		req->msgh_bits = MACH_MSGH_BITS(MACH_MSG_TYPE_COPY_SEND, 
				MACH_MSG_TYPE_MAKE_SEND);
		req->msgh_size = args.req_size;
		req->msgh_remote_port = servport;
		req->msgh_local_port = args.port;
		req->msgh_id = oneway ? 0 : 1;
		if (msg_type == msg_type_complex) {
			(req)->msgh_bits |=  MACH_MSGH_BITS_COMPLEX;
			((ipc_complex_message *)req)->body.msgh_descriptor_count = 1;
			((ipc_complex_message *)req)->descriptor.address = ints;
			((ipc_complex_message *)req)->descriptor.size = 
				num_ints * sizeof(u_int32_t);
			((ipc_complex_message *)req)->descriptor.deallocate = FALSE;
			((ipc_complex_message *)req)->descriptor.copy = MACH_MSG_VIRTUAL_COPY;
			((ipc_complex_message *)req)->descriptor.type = MACH_MSG_OOL_DESCRIPTOR;
		}
		if (verbose) 
			printf("client sending message %d\n", idx);
		ret = mach_msg(req,  
				MACH_SEND_MSG, 
				args.req_size, 
				0, 
				MACH_PORT_NULL,  
				MACH_MSG_TIMEOUT_NONE, 
				MACH_PORT_NULL);
		if (MACH_MSG_SUCCESS != ret) {
			mach_error("mach_msg (send): ", ret);
			fprintf(stderr, "bailing after %u iterations\n", idx);
			exit(1);
			break;
		}
		if (!oneway) {
			if (verbose) 
				printf("client awaiting reply %d\n", idx);
			reply->msgh_bits = 0;
			reply->msgh_size = args.reply_size;
			reply->msgh_local_port = args.port;
			ret = mach_msg(args.reply_msg,  
					MACH_RCV_MSG|MACH_RCV_INTERRUPT, 
					0, 
					args.reply_size, 
					args.port,  
					MACH_MSG_TIMEOUT_NONE, 
					MACH_PORT_NULL);
			if (MACH_MSG_SUCCESS != ret) {
				mach_error("mach_msg (receive): ", ret);
				fprintf(stderr, "bailing after %u iterations\n",
						idx);
				exit(1);
			}
			if (verbose) 
				printf("client received reply %d\n", idx);
		}

		client_work();
	}

	free(ints);
	return NULL;
}