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
struct TYPE_2__ {unsigned char shmem_magic; size_t shmem_pgport; int /*<<< orphan*/  devicename; int /*<<< orphan*/  lock; scalar_t__ rambase; int /*<<< orphan*/ * ioport; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_VALID_CARD (int) ; 
 size_t SRAM_PAGESIZE ; 
 int /*<<< orphan*/  memcpy_fromio (void*,void*,size_t) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 TYPE_1__** sc_adapter ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void memcpy_fromshmem(int card, void *dest, const void *src, size_t n)
{
	unsigned long flags;
	unsigned char ch;

	if(!IS_VALID_CARD(card)) {
		pr_debug("Invalid param: %d is not a valid card id\n", card);
		return;
	}

	if(n > SRAM_PAGESIZE) {
		return;
	}

	/*
	 * determine the page to load from the address
	 */
	ch = (unsigned long) src / SRAM_PAGESIZE;
	pr_debug("%s: loaded page %d\n", sc_adapter[card]->devicename,ch);
	
	
	/*
	 * Block interrupts and load the page
	 */
	spin_lock_irqsave(&sc_adapter[card]->lock, flags);

	outb(((sc_adapter[card]->shmem_magic + ch * SRAM_PAGESIZE) >> 14) | 0x80,
		sc_adapter[card]->ioport[sc_adapter[card]->shmem_pgport]);
	memcpy_fromio(dest,(void *)(sc_adapter[card]->rambase +
		((unsigned long) src % 0x4000)), n);
	spin_unlock_irqrestore(&sc_adapter[card]->lock, flags);
	pr_debug("%s: set page to %#x\n",sc_adapter[card]->devicename,
		((sc_adapter[card]->shmem_magic + ch * SRAM_PAGESIZE)>>14)|0x80);
/*	pr_debug("%s: copying %d bytes from %#x to %#x\n",
		sc_adapter[card]->devicename, n,
		sc_adapter[card]->rambase + ((unsigned long) src %0x4000), (unsigned long) dest); */
}