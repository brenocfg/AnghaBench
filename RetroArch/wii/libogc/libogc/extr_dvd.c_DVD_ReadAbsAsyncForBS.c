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
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {int cmd; int /*<<< orphan*/  cb; scalar_t__ txdsize; int /*<<< orphan*/  offset; int /*<<< orphan*/  len; void* buf; } ;
typedef  TYPE_1__ dvdcmdblk ;
typedef  int /*<<< orphan*/  dvdcbcallback ;

/* Variables and functions */
 int /*<<< orphan*/  __issuecommand (int,TYPE_1__*) ; 

s32 DVD_ReadAbsAsyncForBS(dvdcmdblk *block,void *buf,u32 len,s64 offset,dvdcbcallback cb)
{
	block->cmd = 0x0004;
	block->buf = buf;
	block->len = len;
	block->offset = offset;
	block->txdsize = 0;
	block->cb = cb;

	return __issuecommand(2,block);
}