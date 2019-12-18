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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct memb_blks {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (scalar_t__) ; 

u8 btmemb_ref(struct memb_blks *blk,void *ptr)
{
	u8 ref;
	u32 *pref;
	u32 level;

	_CPU_ISR_Disable(level);
	pref = ptr-sizeof(u32);
	ref = ++(*pref);
	_CPU_ISR_Restore(level);
	return ref;
}