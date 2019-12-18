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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct memb_blks {int size; int num; int /*<<< orphan*/ * mem; } ;
typedef  int s32 ;

/* Variables and functions */
 int MEM_ALIGN_SIZE (int) ; 
 scalar_t__ ROUNDDOWN32 (int) ; 
 int /*<<< orphan*/  SYS_GetArena2Hi () ; 
 int /*<<< orphan*/  SYS_GetArena2Lo () ; 
 int /*<<< orphan*/  SYS_SetArena2Hi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btmemb_init (struct memb_blks*) ; 

__attribute__((used)) static s32 __initUsbIOBuffer(struct memb_blks *blk,u32 buf_size,u32 num_bufs)
{
	u32 len;
	u8 *ptr = NULL;

	len = ((MEM_ALIGN_SIZE(buf_size)+sizeof(u32))*num_bufs);
	ptr = (u8*)ROUNDDOWN32(((u32)SYS_GetArena2Hi() - len));
	if((u32)ptr<(u32)SYS_GetArena2Lo()) return -4;

	SYS_SetArena2Hi(ptr);

	blk->size = buf_size;
	blk->num = num_bufs;
	blk->mem = ptr;

	btmemb_init(blk);
	return 0;
}