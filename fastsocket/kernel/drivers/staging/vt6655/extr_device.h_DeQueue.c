#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tail; int head; int /*<<< orphan*/  packet_num; int /*<<< orphan*/ ** Q; } ;
struct TYPE_5__ {TYPE_1__ rxManeQueue; } ;
typedef  int /*<<< orphan*/ * PSRxMgmtPacket ;
typedef  TYPE_2__* PSDevice ;

/* Variables and functions */
 int NUM ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) inline  static  PSRxMgmtPacket DeQueue (PSDevice pDevice)
{
	PSRxMgmtPacket  pRxMgmtPacket;
	if (pDevice->rxManeQueue.tail == pDevice->rxManeQueue.head)
	{
		printk("Queue is Empty\n");
		return NULL;
	}
	else
	{
		int	x;
		//x=pDevice->rxManeQueue.head = (pDevice->rxManeQueue.head+1)%NUM;
		pDevice->rxManeQueue.head = (pDevice->rxManeQueue.head+1)%NUM;
		x = pDevice->rxManeQueue.head;
		//printk("Enter DeQueue:head is %d\n",x);
		pRxMgmtPacket = pDevice->rxManeQueue.Q[x];
		pDevice->rxManeQueue.packet_num--;
		return pRxMgmtPacket;
	}
}