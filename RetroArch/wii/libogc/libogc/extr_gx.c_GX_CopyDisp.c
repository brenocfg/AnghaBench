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
typedef  int u32 ;
struct TYPE_2__ {int peZMode; int peCMode0; int peCntrl; int dispCopyTL; int dispCopyWH; int dispCopyDst; int dispCopyCntrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int /*<<< orphan*/  MEM_VIRTUAL_TO_PHYSICAL (void*) ; 
 int _SHIFTL (int,int,int) ; 
 int _SHIFTR (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* __gx ; 

void GX_CopyDisp(void *dest,u8 clear)
{
	u8 clflag;
	u32 val;

	if(clear) {
		val= (__gx->peZMode&~0xf)|0xf;
		GX_LOAD_BP_REG(val);
		val = (__gx->peCMode0&~0x3);
		GX_LOAD_BP_REG(val);
	}

	clflag = 0;
	if(clear || (__gx->peCntrl&0x7)==0x0003) {
		if(__gx->peCntrl&0x40) {
			clflag = 1;
			val = (__gx->peCntrl&~0x40);
			GX_LOAD_BP_REG(val);
		}
	}

	GX_LOAD_BP_REG(__gx->dispCopyTL);  // set source top
	GX_LOAD_BP_REG(__gx->dispCopyWH);

	GX_LOAD_BP_REG(__gx->dispCopyDst);

	val = 0x4b000000|(_SHIFTR(MEM_VIRTUAL_TO_PHYSICAL(dest),5,24));
	GX_LOAD_BP_REG(val);

	__gx->dispCopyCntrl = (__gx->dispCopyCntrl&~0x800)|(_SHIFTL(clear,11,1));
	__gx->dispCopyCntrl = (__gx->dispCopyCntrl&~0x4000)|0x4000;
	__gx->dispCopyCntrl = (__gx->dispCopyCntrl&~0xff000000)|(_SHIFTL(0x52,24,8));

	GX_LOAD_BP_REG(__gx->dispCopyCntrl);

	if(clear) {
		GX_LOAD_BP_REG(__gx->peZMode);
		GX_LOAD_BP_REG(__gx->peCMode0);
	}
	if(clflag) GX_LOAD_BP_REG(__gx->peCntrl);
}