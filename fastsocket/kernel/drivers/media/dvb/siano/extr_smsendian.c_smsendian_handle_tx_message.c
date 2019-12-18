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
struct SmsMsgHdr_ST {int dummy; } ;
struct TYPE_2__ {int msgType; int /*<<< orphan*/  msgLength; } ;
struct SmsMsgData_ST {void** msgData; TYPE_1__ xMsgHeader; } ;

/* Variables and functions */
#define  MSG_SMS_DATA_DOWNLOAD_REQ 128 
 void* le32_to_cpu (void*) ; 

void smsendian_handle_tx_message(void *buffer)
{
#ifdef __BIG_ENDIAN
	struct SmsMsgData_ST *msg = (struct SmsMsgData_ST *)buffer;
	int i;
	int msgWords;

	switch (msg->xMsgHeader.msgType) {
	case MSG_SMS_DATA_DOWNLOAD_REQ:
	{
		msg->msgData[0] = le32_to_cpu(msg->msgData[0]);
		break;
	}

	default:
		msgWords = (msg->xMsgHeader.msgLength -
				sizeof(struct SmsMsgHdr_ST))/4;

		for (i = 0; i < msgWords; i++)
			msg->msgData[i] = le32_to_cpu(msg->msgData[i]);

		break;
	}
#endif /* __BIG_ENDIAN */
}