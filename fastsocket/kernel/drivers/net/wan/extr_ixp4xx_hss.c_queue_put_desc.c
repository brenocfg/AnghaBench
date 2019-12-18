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
typedef  int u32 ;
struct desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  debug_desc (int,struct desc*) ; 
 int /*<<< orphan*/  qmgr_put_entry (unsigned int,int) ; 

__attribute__((used)) static inline void queue_put_desc(unsigned int queue, u32 phys,
				  struct desc *desc)
{
	debug_desc(phys, desc);
	BUG_ON(phys & 0x1F);
	qmgr_put_entry(queue, phys);
	/* Don't check for queue overflow here, we've allocated sufficient
	   length and queues >= 32 don't support this check anyway. */
}