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
struct mem_chunk {int dummy; } ;

/* Variables and functions */
 int MEMORY_CHUNKS ; 
 int /*<<< orphan*/  __ctl_clear_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __ctl_load (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ctl_store (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_local_irq_ssm (unsigned long) ; 
 unsigned long __raw_local_irq_stnsm (int) ; 
 int /*<<< orphan*/  find_memory_chunks (struct mem_chunk*) ; 
 int /*<<< orphan*/  memset (struct mem_chunk*,int /*<<< orphan*/ ,int) ; 

void detect_memory_layout(struct mem_chunk chunk[])
{
	unsigned long flags, cr0;

	memset(chunk, 0, MEMORY_CHUNKS * sizeof(struct mem_chunk));
	/* Disable IRQs, DAT and low address protection so tprot does the
	 * right thing and we don't get scheduled away with low address
	 * protection disabled.
	 */
	flags = __raw_local_irq_stnsm(0xf8);
	__ctl_store(cr0, 0, 0);
	__ctl_clear_bit(0, 28);
	find_memory_chunks(chunk);
	__ctl_load(cr0, 0, 0);
	__raw_local_irq_ssm(flags);
}