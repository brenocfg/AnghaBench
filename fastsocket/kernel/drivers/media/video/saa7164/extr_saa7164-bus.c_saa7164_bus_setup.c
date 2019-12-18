#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct tmComResBusInfo {scalar_t__ m_dwSetWritePos; scalar_t__ m_dwGetReadPos; scalar_t__ m_dwGetWritePos; scalar_t__ m_dwSetReadPos; void* m_dwSizeGetRing; int /*<<< orphan*/ * m_pdwGetRing; void* m_dwSizeSetRing; int /*<<< orphan*/ * m_pdwSetRing; int /*<<< orphan*/  m_wMaxReqSize; int /*<<< orphan*/  Type; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  BARLocation; } ;
struct TYPE_3__ {int /*<<< orphan*/  ResponseRing; int /*<<< orphan*/  CommandRing; } ;
struct saa7164_dev {TYPE_2__ intfdesc; TYPE_1__ busdesc; scalar_t__ bmmio; struct tmComResBusInfo bus; } ;

/* Variables and functions */
 void* SAA_DEVICE_BUFFERBLOCKSIZE ; 
 int /*<<< orphan*/  SAA_DEVICE_MAXREQUESTSIZE ; 
 int /*<<< orphan*/  TYPE_BUS_PCIe ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int saa7164_bus_setup(struct saa7164_dev *dev)
{
	struct tmComResBusInfo *b	= &dev->bus;

	mutex_init(&b->lock);

	b->Type			= TYPE_BUS_PCIe;
	b->m_wMaxReqSize	= SAA_DEVICE_MAXREQUESTSIZE;

	b->m_pdwSetRing		= (u8 *)(dev->bmmio +
		((u32)dev->busdesc.CommandRing));

	b->m_dwSizeSetRing	= SAA_DEVICE_BUFFERBLOCKSIZE;

	b->m_pdwGetRing		= (u8 *)(dev->bmmio +
		((u32)dev->busdesc.ResponseRing));

	b->m_dwSizeGetRing	= SAA_DEVICE_BUFFERBLOCKSIZE;

	b->m_dwSetWritePos	= ((u32)dev->intfdesc.BARLocation) +
		(2 * sizeof(u64));
	b->m_dwSetReadPos	= b->m_dwSetWritePos + (1 * sizeof(u32));

	b->m_dwGetWritePos	= b->m_dwSetWritePos + (2 * sizeof(u32));
	b->m_dwGetReadPos	= b->m_dwSetWritePos + (3 * sizeof(u32));

	return 0;
}