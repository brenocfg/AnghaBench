#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_msg_timeout_t ;
typedef  int /*<<< orphan*/  mach_msg_size_t ;
typedef  scalar_t__ mach_msg_return_t ;
typedef  int mach_msg_option_t ;
typedef  int /*<<< orphan*/  mach_msg_header_t ;
typedef  int /*<<< orphan*/  ipc_kmsg_t ;
struct TYPE_2__ {int options; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_IPC ; 
 int /*<<< orphan*/  KDBG (int,...) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_IPC_KMSG_INFO ; 
 scalar_t__ MACH_MSG_SUCCESS ; 
 int MACH_SEND_IMPORTANCE ; 
 int MACH_SEND_NOIMPORTANCE ; 
 int TH_OPT_SEND_IMPORTANCE ; 
 TYPE_1__* current_thread () ; 
 scalar_t__ ipc_kmsg_copyin_from_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kmsg_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kmsg_free (int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_kmsg_get_from_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ipc_kmsg_send (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

mach_msg_return_t
mach_msg_send_from_kernel_with_options(
	mach_msg_header_t	*msg,
	mach_msg_size_t		send_size,
	mach_msg_option_t	option,
	mach_msg_timeout_t	timeout_val)
{
	ipc_kmsg_t kmsg;
	mach_msg_return_t mr;

	KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_START);

	mr = ipc_kmsg_get_from_kernel(msg, send_size, &kmsg);
	if (mr != MACH_MSG_SUCCESS) {
		KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_END, mr);
		return mr;
	}

	mr = ipc_kmsg_copyin_from_kernel(kmsg);
	if (mr != MACH_MSG_SUCCESS) {
		ipc_kmsg_free(kmsg);
		KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_END, mr);
		return mr;
	}

	/*
	 * Until we are sure of its effects, we are disabling
	 * importance donation from the kernel-side of user
	 * threads in importance-donating tasks - unless the
	 * option to force importance donation is passed in,
	 * or the thread's SEND_IMPORTANCE option has been set.
	 * (11938665 & 23925818)
	 */
	if (current_thread()->options & TH_OPT_SEND_IMPORTANCE)
		option &= ~MACH_SEND_NOIMPORTANCE;
	else if ((option & MACH_SEND_IMPORTANCE) == 0)
		option |= MACH_SEND_NOIMPORTANCE;

	mr = ipc_kmsg_send(kmsg, option, timeout_val);

	if (mr != MACH_MSG_SUCCESS) {
		ipc_kmsg_destroy(kmsg);
		KDBG(MACHDBG_CODE(DBG_MACH_IPC,MACH_IPC_KMSG_INFO) | DBG_FUNC_END, mr);
	}
	
	return mr;
}