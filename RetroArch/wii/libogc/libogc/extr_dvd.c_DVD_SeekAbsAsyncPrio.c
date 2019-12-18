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
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {int cmd; int /*<<< orphan*/  cb; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ dvdcmdblk ;
typedef  int /*<<< orphan*/  dvdcbcallback ;

/* Variables and functions */
 int /*<<< orphan*/  __issuecommand (int /*<<< orphan*/ ,TYPE_1__*) ; 

s32 DVD_SeekAbsAsyncPrio(dvdcmdblk *block,s64 offset,dvdcbcallback cb,s32 prio)
{
	block->cmd = 0x0002;
	block->offset = offset;
	block->cb = cb;

	return __issuecommand(prio,block);
}