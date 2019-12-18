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
typedef  int u8 ;
typedef  int s32 ;
struct TYPE_2__ {int VATTable; int /*<<< orphan*/ * VAT2reg; int /*<<< orphan*/ * VAT1reg; int /*<<< orphan*/ * VAT0reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_CP_REG (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* __gx ; 

__attribute__((used)) static void __GX_SetVAT()
{
	u8 setvtx = 0;
	s32 i;

	for(i=0;i<8;i++) {
		setvtx = (1<<i);
		if(__gx->VATTable&setvtx) {
			GX_LOAD_CP_REG((0x70+(i&7)),__gx->VAT0reg[i]);
			GX_LOAD_CP_REG((0x80+(i&7)),__gx->VAT1reg[i]);
			GX_LOAD_CP_REG((0x90+(i&7)),__gx->VAT2reg[i]);
		}
	}
	__gx->VATTable = 0;
}