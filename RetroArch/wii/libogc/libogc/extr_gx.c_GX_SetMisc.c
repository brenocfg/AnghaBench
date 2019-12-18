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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int xfFlush; int dirtyState; scalar_t__ saveDLctx; scalar_t__ xfFlushSafe; int /*<<< orphan*/  xfFlushExp; } ;

/* Variables and functions */
 scalar_t__ GX_MT_DL_SAVE_CTX ; 
 scalar_t__ GX_MT_XF_FLUSH ; 
 int /*<<< orphan*/  _SHIFTR (scalar_t__,int,int) ; 
 TYPE_1__* __gx ; 
 scalar_t__ cntlzw (scalar_t__) ; 

void GX_SetMisc(u32 token,u32 value)
{
	u32 cnt;

	if(token==GX_MT_XF_FLUSH) {
		__gx->xfFlushSafe = value;
		cnt = cntlzw(__gx->xfFlushSafe);
		__gx->xfFlushExp = _SHIFTR(cnt,5,16);

		__gx->xfFlush = 1;
		if(!__gx->xfFlushSafe) return;

		__gx->dirtyState |= 0x0008;
	} else if(token==GX_MT_DL_SAVE_CTX) {
		__gx->saveDLctx = (value&0xff);
	}
	return;
}