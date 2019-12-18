#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ packet_num; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pMgmt; TYPE_1__ rxManeQueue; } ;
typedef  int /*<<< orphan*/  PSRxMgmtPacket ;
typedef  TYPE_2__* PSDevice ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  DeQueue (TYPE_2__*) ; 
 scalar_t__ mlme_kill ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vMgrRxManagePacket (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

INT MlmeThread(
     void * Context)
{
	PSDevice	pDevice =  (PSDevice) Context;
	PSRxMgmtPacket			pRxMgmtPacket;
	// int i ;
	//complete(&pDevice->notify);
//printk("Enter MngWorkItem,Queue packet num is %d\n",pDevice->rxManeQueue.packet_num);

	//printk("Enter MlmeThread,packet _num is %d\n",pDevice->rxManeQueue.packet_num);
	//i = 0;
#if 1
	while (1)
	{

	//printk("DDDD\n");
	//down(&pDevice->mlme_semaphore);
        // pRxMgmtPacket =  DeQueue(pDevice);
#if 1
		spin_lock_irq(&pDevice->lock);
		 while(pDevice->rxManeQueue.packet_num != 0)
	 	{
			 pRxMgmtPacket =  DeQueue(pDevice);
        			//pDevice;
        			//DequeueManageObject(pDevice->FirstRecvMngList, pDevice->LastRecvMngList);
			vMgrRxManagePacket(pDevice, pDevice->pMgmt, pRxMgmtPacket);
			//printk("packet_num is %d\n",pDevice->rxManeQueue.packet_num);

		 }
		spin_unlock_irq(&pDevice->lock);
		if (mlme_kill == 0)
		break;
		//udelay(200);
#endif
	//printk("Before schedule thread jiffies is %x\n",jiffies);
	schedule();
	//printk("after schedule thread jiffies is %x\n",jiffies);
	if (mlme_kill == 0)
		break;
	//printk("i is %d\n",i);
	}

#endif
	return 0;

}