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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  mtxIdxHi; int /*<<< orphan*/  mtxIdxLo; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_CP_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_LOAD_XF_REG (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* __gx ; 

__attribute__((used)) static void __GX_SetMatrixIndex(u32 mtx)
{
	if(mtx<5) {
		GX_LOAD_CP_REG(0x30,__gx->mtxIdxLo);
		GX_LOAD_XF_REG(0x1018,__gx->mtxIdxLo);
	} else {
		GX_LOAD_CP_REG(0x40,__gx->mtxIdxHi);
		GX_LOAD_XF_REG(0x1019,__gx->mtxIdxHi);
	}
}