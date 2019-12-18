#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {int cmd; int state; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ dvdcmdblk ;

/* Variables and functions */
 int /*<<< orphan*/  DCInvalidateRange (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 scalar_t__ __dvd_autoinvalidation ; 
 int /*<<< orphan*/  __dvd_executing ; 
 int /*<<< orphan*/  __dvd_pushwaitingqueue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  __dvd_stateready () ; 

s32 __issuecommand(s32 prio,dvdcmdblk *block)
{
	s32 ret;
	u32 level;
	if(__dvd_autoinvalidation &&
		(block->cmd==0x0001 || block->cmd==0x00004
		|| block->cmd==0x0005 || block->cmd==0x000e)) DCInvalidateRange(block->buf,block->len);

	_CPU_ISR_Disable(level);
	block->state = 0x0002;
	ret = __dvd_pushwaitingqueue(prio,block);
	if(!__dvd_executing) __dvd_stateready();
	_CPU_ISR_Restore(level);
	return ret;
}