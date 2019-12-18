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
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  dvddrvinfo ;
struct TYPE_4__ {int cmd; int len; int /*<<< orphan*/  cb; scalar_t__ txdsize; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ dvdcmdblk ;
typedef  int /*<<< orphan*/  dvdcbcallback ;

/* Variables and functions */
 int /*<<< orphan*/  __issuecommand (int,TYPE_1__*) ; 

s32 DVD_InquiryAsync(dvdcmdblk *block,dvddrvinfo *info,dvdcbcallback cb)
{
	block->cmd = 0x000e;
	block->buf = info;
	block->len = 0x20;
	block->txdsize = 0;
	block->cb = cb;
	return __issuecommand(2,block);
}