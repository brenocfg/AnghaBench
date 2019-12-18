#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct fib {int hw_fib_pa; TYPE_4__* hw_fib_va; struct aac_dev* dev; } ;
struct aac_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  numpending; } ;
struct aac_fib_xporthdr {void* Size; int /*<<< orphan*/  HostAddress; void* Handle; } ;
struct aac_dev {scalar_t__ comm_interface; TYPE_1__* queues; } ;
typedef  int dma_addr_t ;
struct TYPE_10__ {int /*<<< orphan*/  IQ_L; int /*<<< orphan*/  IQ_H; } ;
struct TYPE_7__ {scalar_t__ TimeStamp; } ;
struct TYPE_8__ {int SenderFibAddress; int Handle; TYPE_2__ u; int /*<<< orphan*/  StructType; int /*<<< orphan*/  Size; } ;
struct TYPE_9__ {TYPE_3__ header; } ;
struct TYPE_6__ {struct aac_queue* queue; } ;

/* Variables and functions */
 scalar_t__ AAC_COMM_MESSAGE_TYPE2 ; 
 int ALIGN32 ; 
 size_t AdapNormCmdQueue ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  FIB_MAGIC2 ; 
 TYPE_5__ MUnit ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  src_writel (struct aac_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aac_src_deliver_message(struct fib *fib)
{
	struct aac_dev *dev = fib->dev;
	struct aac_queue *q = &dev->queues->queue[AdapNormCmdQueue];
	unsigned long qflags;
	u32 fibsize;
	dma_addr_t address;
	struct aac_fib_xporthdr *pFibX;
	u16 hdr_size = le16_to_cpu(fib->hw_fib_va->header.Size);

	spin_lock_irqsave(q->lock, qflags);
	q->numpending++;
	spin_unlock_irqrestore(q->lock, qflags);

	if (dev->comm_interface == AAC_COMM_MESSAGE_TYPE2) {
		/* Calculate the amount to the fibsize bits */
		fibsize = (hdr_size + 127) / 128 - 1;
		if (fibsize > (ALIGN32 - 1))
			return -EMSGSIZE;
		/* New FIB header, 32-bit */
		address = fib->hw_fib_pa;
		fib->hw_fib_va->header.StructType = FIB_MAGIC2;
		fib->hw_fib_va->header.SenderFibAddress = (u32)address;
		fib->hw_fib_va->header.u.TimeStamp = 0;
		BUG_ON((u32)(address >> 32) != 0L);
		address |= fibsize;
	} else {
		/* Calculate the amount to the fibsize bits */
		fibsize = (sizeof(struct aac_fib_xporthdr) + hdr_size + 127) / 128 - 1;
		if (fibsize > (ALIGN32 - 1))
			return -EMSGSIZE;

		/* Fill XPORT header */
		pFibX = (void *)fib->hw_fib_va - sizeof(struct aac_fib_xporthdr);
		pFibX->Handle = cpu_to_le32(fib->hw_fib_va->header.Handle);
		pFibX->HostAddress = cpu_to_le64(fib->hw_fib_pa);
		pFibX->Size = cpu_to_le32(hdr_size);

		/*
		 * The xport header has been 32-byte aligned for us so that fibsize
		 * can be masked out of this address by hardware. -- BenC
		 */
		address = fib->hw_fib_pa - sizeof(struct aac_fib_xporthdr);
		if (address & (ALIGN32 - 1))
			return -EINVAL;
		address |= fibsize;
	}

	src_writel(dev, MUnit.IQ_H, (address >> 32) & 0xffffffff);
	src_writel(dev, MUnit.IQ_L, address & 0xffffffff);

	return 0;
}