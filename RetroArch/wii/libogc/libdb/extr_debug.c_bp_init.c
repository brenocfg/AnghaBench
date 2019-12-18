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
typedef  size_t s32 ;
struct TYPE_2__ {int instr; int /*<<< orphan*/ * next; int /*<<< orphan*/ * address; } ;

/* Variables and functions */
 size_t GEKKO_MAX_BP ; 
 TYPE_1__* bp_entries ; 

__attribute__((used)) static __inline__ void bp_init()
{
	s32 i;

	for(i=0;i<GEKKO_MAX_BP;i++) {
		bp_entries[i].address = NULL;
		bp_entries[i].instr = 0xffffffff;
		bp_entries[i].next = NULL;
	}
}