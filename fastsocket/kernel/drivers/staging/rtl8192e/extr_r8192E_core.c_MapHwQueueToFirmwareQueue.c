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
typedef  int u8 ;

/* Variables and functions */
#define  BEACON_QUEUE 135 
#define  BE_QUEUE 134 
#define  BK_QUEUE 133 
 int /*<<< orphan*/  COMP_ERR ; 
#define  HIGH_QUEUE 132 
#define  MGNT_QUEUE 131 
 int QSLT_BE ; 
 int QSLT_BEACON ; 
 int QSLT_BK ; 
 int QSLT_CMD ; 
 int QSLT_MGNT ; 
 int QSLT_VI ; 
 int QSLT_VO ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
#define  TXCMD_QUEUE 130 
#define  VI_QUEUE 129 
#define  VO_QUEUE 128 

__attribute__((used)) static u8 MapHwQueueToFirmwareQueue(u8 QueueID)
{
	u8 QueueSelect = 0x0;       //defualt set to

	switch(QueueID) {
		case BE_QUEUE:
			QueueSelect = QSLT_BE;  //or QSelect = pTcb->priority;
			break;

		case BK_QUEUE:
			QueueSelect = QSLT_BK;  //or QSelect = pTcb->priority;
			break;

		case VO_QUEUE:
			QueueSelect = QSLT_VO;  //or QSelect = pTcb->priority;
			break;

		case VI_QUEUE:
			QueueSelect = QSLT_VI;  //or QSelect = pTcb->priority;
			break;
		case MGNT_QUEUE:
			QueueSelect = QSLT_MGNT;
			break;

		case BEACON_QUEUE:
			QueueSelect = QSLT_BEACON;
			break;

			// TODO: 2006.10.30 mark other queue selection until we verify it is OK
			// TODO: Remove Assertions
//#if (RTL819X_FPGA_VER & RTL819X_FPGA_GUANGAN_070502)
		case TXCMD_QUEUE:
			QueueSelect = QSLT_CMD;
			break;
//#endif
		case HIGH_QUEUE:
			//QueueSelect = QSLT_HIGH;
			//break;

		default:
			RT_TRACE(COMP_ERR, "TransmitTCB(): Impossible Queue Selection: %d \n", QueueID);
			break;
	}
	return QueueSelect;
}