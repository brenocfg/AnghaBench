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
struct TYPE_4__ {int /*<<< orphan*/  chn; } ;
typedef  TYPE_1__ card_file ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_WriteAsync (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __card_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __card_synccallback ; 

s32 CARD_Write(card_file *file,void *buffer,u32 len,u32 offset)
{
	s32 ret;

	if((ret=CARD_WriteAsync(file,buffer,len,offset,__card_synccallback))>=0) {
		ret = __card_sync(file->chn);
	}
	return ret;
}