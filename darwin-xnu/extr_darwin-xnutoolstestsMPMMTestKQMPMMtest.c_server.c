#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_address_t ;
struct port_args {int server_num; int /*<<< orphan*/  reply_size; TYPE_3__* reply_msg; TYPE_3__* req_msg; int /*<<< orphan*/  pset; int /*<<< orphan*/  req_size; scalar_t__ port; } ;
struct kevent64_s {scalar_t__ data; } ;
typedef  int kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  size; scalar_t__ address; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;
typedef  TYPE_2__ ipc_complex_message ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_6__ {int msgh_bits; int msgh_id; scalar_t__ msgh_local_port; int /*<<< orphan*/  msgh_remote_port; int /*<<< orphan*/  msgh_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_MACHPORT ; 
 int EV_ADD ; 
 int EV_CLEAR ; 
 int EV_DISPATCH ; 
 int EV_ENABLE ; 
 int /*<<< orphan*/  EV_SET64 (struct kevent64_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int MACH_MSGH_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACH_MSGH_BITS_COMPLEX ; 
 int MACH_MSG_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TIMEOUT_NONE ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_COPY_SEND ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_MAKE_SEND ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int MACH_RCV_INTERRUPT ; 
 int MACH_RCV_INTERRUPTED ; 
 int MACH_RCV_LARGE ; 
 int MACH_RCV_MSG ; 
 int MACH_SEND_MSG ; 
 scalar_t__ do_select ; 
 int /*<<< orphan*/  exit (int) ; 
 int kevent64 (int,struct kevent64_s*,int,struct kevent64_s*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kqueue () ; 
 int /*<<< orphan*/  mach_error (char*,int) ; 
 int mach_msg (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int num_clients ; 
 int num_msgs ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_server_ports (struct port_args*) ; 
 int /*<<< orphan*/  thread_setup (int) ; 
 scalar_t__ verbose ; 
 int vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
server(void *serverarg) 
{
	int kq;
	struct kevent64_s kev[1];
	int err;
	int count;
	struct port_args args;
	int idx;
	kern_return_t ret;
	int totalmsg = num_msgs * num_clients;
	fd_set readfds;

	args.server_num = (int) (long) serverarg;
	setup_server_ports(&args);

	thread_setup(args.server_num + 1);
	
	kq = kqueue();
	if (kq == -1) {
		perror("kqueue");
		exit(1);
	}
	EV_SET64(&kev[0], args.pset, EVFILT_MACHPORT, (EV_ADD | EV_CLEAR | EV_DISPATCH), 
#if DIRECT_MSG_RCV
		 MACH_RCV_MSG|MACH_RCV_LARGE, 0, 0, (mach_vm_address_t)args.req_msg, args.req_size);
#else
		0, 0, 0, 0, 0);
#endif
	err = kevent64(kq, kev, 1, NULL, 0, 0, NULL);
	if (err == -1) {
		perror("kevent");
		exit(1);
	}
	
	for (idx = 0; idx < totalmsg; idx++) {

		if (verbose) 
			printf("server awaiting message %d\n", idx);
	retry:
		if (do_select) {
			FD_ZERO(&readfds);
			FD_SET(kq, &readfds);

			if (verbose)
				printf("Calling select() prior to kevent64().\n");

			count = select(kq + 1, &readfds, NULL, NULL, NULL);
			if (count == -1) {
				perror("select");
				exit(1);
			}
		}

		EV_SET64(&kev[0], args.pset, EVFILT_MACHPORT, EV_ENABLE, 
#if DIRECT_MSG_RCV
			 MACH_RCV_MSG|MACH_RCV_LARGE, 0, 0, (mach_vm_address_t)args.req_msg, args.req_size);
#else
			0, 0, 0, 0, 0);
#endif
		err = kevent64(kq, kev, 1, kev, 1, 0, NULL);
		if (err == -1) {
			perror("kevent64");
			exit(1);
		}		
		if (err == 0) {
		  // printf("kevent64: returned zero\n");
			goto retry;
		}

#if DIRECT_MSG_RCV
		ret = kev[0].fflags;
		if (MACH_MSG_SUCCESS != ret) {
			if (verbose)
				printf("kevent64() mach_msg_return=%d", ret);
			mach_error("kevent64 (msg receive): ", ret);
			exit(1);
		} 
#else
		if (kev[0].data != args.port)
			printf("kevent64(MACH_PORT_NULL) port name (%lld) != expected (0x%x)\n", kev[0].data, args.port);

		args.req_msg->msgh_bits = 0;
		args.req_msg->msgh_size = args.req_size;
		args.req_msg->msgh_local_port = args.port;
		ret = mach_msg(args.req_msg,  
				MACH_RCV_MSG|MACH_RCV_INTERRUPT|MACH_RCV_LARGE, 
				0, 
				args.req_size,  
				args.pset, 
				MACH_MSG_TIMEOUT_NONE, 
				MACH_PORT_NULL);
		if (MACH_RCV_INTERRUPTED == ret)
			break;
		if (MACH_MSG_SUCCESS != ret) {
			if (verbose)
				printf("mach_msg() ret=%d", ret);
			mach_error("mach_msg (receive): ", ret);
			exit(1);
		}
#endif
		if (verbose)
			printf("server received message %d\n", idx);
		if (args.req_msg->msgh_bits & MACH_MSGH_BITS_COMPLEX) {
			ret = vm_deallocate(mach_task_self(),  
					(vm_address_t)((ipc_complex_message *)args.req_msg)->descriptor.address,  
					((ipc_complex_message *)args.req_msg)->descriptor.size);
		}

		if (1 == args.req_msg->msgh_id) {
			if (verbose) 
				printf("server sending reply %d\n", idx);
			args.reply_msg->msgh_bits = MACH_MSGH_BITS(MACH_MSG_TYPE_COPY_SEND,  
					MACH_MSG_TYPE_MAKE_SEND);
			args.reply_msg->msgh_size = args.reply_size;
			args.reply_msg->msgh_remote_port = args.req_msg->msgh_remote_port;
			args.reply_msg->msgh_local_port = args.req_msg->msgh_local_port;
			args.reply_msg->msgh_id = 2;
			ret = mach_msg(args.reply_msg, 
					MACH_SEND_MSG, 
					args.reply_size, 
					0, 
					MACH_PORT_NULL, 
					MACH_MSG_TIMEOUT_NONE,  
					MACH_PORT_NULL);
			if (MACH_MSG_SUCCESS != ret) {
				mach_error("mach_msg (send): ", ret);
				exit(1);
			}
		}
	}
	return NULL;
}