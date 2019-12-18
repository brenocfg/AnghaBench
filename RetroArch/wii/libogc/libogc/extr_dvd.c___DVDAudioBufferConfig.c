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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {int cmd; int /*<<< orphan*/  cb; void* len; void* offset; } ;
typedef  TYPE_1__ dvdcmdblk ;
typedef  int /*<<< orphan*/  dvdcbcallback ;

/* Variables and functions */
 int /*<<< orphan*/  __issuecommand (int,TYPE_1__*) ; 

s32 __DVDAudioBufferConfig(dvdcmdblk *block,u32 enable,u32 size,dvdcbcallback cb)
{
	if(!block) return 0;

	block->cmd = 0x000d;
	block->offset = enable;
	block->len = size;
	block->cb = cb;

	return __issuecommand(2,block);
}