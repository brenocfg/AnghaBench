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
struct msg_queue {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IPC_INFO 133 
#define  IPC_RMID 132 
#define  IPC_SET 131 
#define  IPC_STAT 130 
 int MAY_READ ; 
 int MAY_READWRITE ; 
#define  MSG_INFO 129 
#define  MSG_STAT 128 
 int smk_curacc_msq (struct msg_queue*,int) ; 

__attribute__((used)) static int smack_msg_queue_msgctl(struct msg_queue *msq, int cmd)
{
	int may;

	switch (cmd) {
	case IPC_STAT:
	case MSG_STAT:
		may = MAY_READ;
		break;
	case IPC_SET:
	case IPC_RMID:
		may = MAY_READWRITE;
		break;
	case IPC_INFO:
	case MSG_INFO:
		/*
		 * System level information
		 */
		return 0;
	default:
		return -EINVAL;
	}

	return smk_curacc_msq(msq, may);
}