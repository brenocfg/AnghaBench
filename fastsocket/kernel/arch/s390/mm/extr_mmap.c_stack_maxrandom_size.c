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
struct TYPE_2__ {int flags; int personality; } ;

/* Variables and functions */
 int ADDR_NO_RANDOMIZE ; 
 unsigned long PAGE_SHIFT ; 
 int PF_RANDOMIZE ; 
 unsigned long STACK_RND_MASK ; 
 TYPE_1__* current ; 

__attribute__((used)) static unsigned long stack_maxrandom_size(void)
{
	if (!(current->flags & PF_RANDOMIZE))
		return 0;
	if (current->personality & ADDR_NO_RANDOMIZE)
		return 0;
	return STACK_RND_MASK << PAGE_SHIFT;
}