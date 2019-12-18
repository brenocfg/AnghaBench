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
struct SmsVersionRes_ST {int /*<<< orphan*/  ChipModel; } ;
struct SmsMsgHdr_ST {int dummy; } ;
struct TYPE_2__ {int msgType; int /*<<< orphan*/  msgLength; } ;
struct SmsMsgData_ST {int /*<<< orphan*/ * msgData; TYPE_1__ xMsgHeader; } ;

/* Variables and functions */
#define  MSG_SMS_DAB_CHANNEL 131 
#define  MSG_SMS_DATA_MSG 130 
#define  MSG_SMS_DVBT_BDA_DATA 129 
#define  MSG_SMS_GET_VERSION_EX_RES 128 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

void smsendian_handle_rx_message(void *buffer)
{
#ifdef __BIG_ENDIAN
	struct SmsMsgData_ST *msg = (struct SmsMsgData_ST *)buffer;
	int i;
	int msgWords;

	switch (msg->xMsgHeader.msgType) {
	case MSG_SMS_GET_VERSION_EX_RES:
	{
		struct SmsVersionRes_ST *ver =
			(struct SmsVersionRes_ST *) msg;
		ver->ChipModel = le16_to_cpu(ver->ChipModel);
		break;
	}

	case MSG_SMS_DVBT_BDA_DATA:
	case MSG_SMS_DAB_CHANNEL:
	case MSG_SMS_DATA_MSG:
	{
		break;
	}

	default:
	{
		msgWords = (msg->xMsgHeader.msgLength -
				sizeof(struct SmsMsgHdr_ST))/4;

		for (i = 0; i < msgWords; i++)
			msg->msgData[i] = le32_to_cpu(msg->msgData[i]);

		break;
	}
	}
#endif /* __BIG_ENDIAN */
}