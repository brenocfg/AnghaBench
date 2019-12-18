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

/* Variables and functions */
#define  DLM_MSG_CANCEL 132 
 int DLM_MSG_CANCEL_REPLY ; 
#define  DLM_MSG_CONVERT 131 
 int DLM_MSG_CONVERT_REPLY ; 
#define  DLM_MSG_LOOKUP 130 
 int DLM_MSG_LOOKUP_REPLY ; 
#define  DLM_MSG_REQUEST 129 
 int DLM_MSG_REQUEST_REPLY ; 
#define  DLM_MSG_UNLOCK 128 
 int DLM_MSG_UNLOCK_REPLY ; 

__attribute__((used)) static int msg_reply_type(int mstype)
{
	switch (mstype) {
	case DLM_MSG_REQUEST:
		return DLM_MSG_REQUEST_REPLY;
	case DLM_MSG_CONVERT:
		return DLM_MSG_CONVERT_REPLY;
	case DLM_MSG_UNLOCK:
		return DLM_MSG_UNLOCK_REPLY;
	case DLM_MSG_CANCEL:
		return DLM_MSG_CANCEL_REPLY;
	case DLM_MSG_LOOKUP:
		return DLM_MSG_LOOKUP_REPLY;
	}
	return -1;
}