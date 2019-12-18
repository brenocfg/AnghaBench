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
struct TYPE_2__ {int /*<<< orphan*/  vcdHi; int /*<<< orphan*/  vcdLo; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_CP_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_XfVtxSpecs () ; 
 TYPE_1__* __gx ; 

__attribute__((used)) static void __GX_SetVCD()
{
	GX_LOAD_CP_REG(0x50,__gx->vcdLo);
	GX_LOAD_CP_REG(0x60,__gx->vcdHi);
	__GX_XfVtxSpecs();
}