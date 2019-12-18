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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Adapter ; 
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ RT_USB_CANNOT_IO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WFM5 ; 
 scalar_t__ read_nic_dword (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void ChkFwCmdIoDone(struct net_device* dev)
{
	u16 PollingCnt = 1000;
	u32 tmpValue;

	do
	{// Make sure that CMD IO has be accepted by FW.
#ifdef TO_DO_LIST
		if(RT_USB_CANNOT_IO(Adapter))
		{
			RT_TRACE(COMP_CMD, "ChkFwCmdIoDone(): USB can NOT IO!!\n");
			return;
		}
#endif
		udelay(10); // sleep 20us
		tmpValue = read_nic_dword(dev, WFM5);
		if(tmpValue == 0)
		{
			RT_TRACE(COMP_CMD, "[FW CMD] Set FW Cmd success!!\n");
			break;
		}
		else
		{
			RT_TRACE(COMP_CMD, "[FW CMD] Polling FW Cmd PollingCnt(%d)!!\n", PollingCnt);
		}
	}while( --PollingCnt );

	if(PollingCnt == 0)
	{
		RT_TRACE(COMP_ERR, "[FW CMD] Set FW Cmd fail!!\n");
	}
}