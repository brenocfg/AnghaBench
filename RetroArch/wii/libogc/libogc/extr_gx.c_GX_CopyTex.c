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
struct TYPE_2__ {int peZMode; int peCMode0; int peCntrl; int texCopyTL; int texCopyWH; int texCopyDst; int texCopyCntrl; scalar_t__ texCopyZTex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int /*<<< orphan*/  MEM_VIRTUAL_TO_PHYSICAL (void*) ; 
 int _SHIFTL (int,int,int) ; 
 int _SHIFTR (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* __gx ; 

void GX_CopyTex(void *dest,u8 clear)
{
	u8 clflag;
	u32 val;

	if(clear) {
		val = (__gx->peZMode&~0xf)|0xf;
		GX_LOAD_BP_REG(val);
		val = (__gx->peCMode0&~0x3);
		GX_LOAD_BP_REG(val);
	}

	clflag = 0;
	val = __gx->peCntrl;
	if(__gx->texCopyZTex && (val&0x7)!=0x0003) {
		clflag = 1;
		val = (val&~0x7)|0x0003;
	}
	if(clear || (val&0x7)==0x0003) {
		if(val&0x40) {
			clflag = 1;
			val = (val&~0x40);
		}
	}
	if(clflag) GX_LOAD_BP_REG(val);

	val = 0x4b000000|(_SHIFTR(MEM_VIRTUAL_TO_PHYSICAL(dest),5,24));

	GX_LOAD_BP_REG(__gx->texCopyTL);
	GX_LOAD_BP_REG(__gx->texCopyWH);
	GX_LOAD_BP_REG(__gx->texCopyDst);
	GX_LOAD_BP_REG(val);

	__gx->texCopyCntrl = (__gx->texCopyCntrl&~0x800)|(_SHIFTL(clear,11,1));
	__gx->texCopyCntrl = (__gx->texCopyCntrl&~0x4000);
	__gx->texCopyCntrl = (__gx->texCopyCntrl&~0xff000000)|(_SHIFTL(0x52,24,8));
	GX_LOAD_BP_REG(__gx->texCopyCntrl);

	if(clear) {
		GX_LOAD_BP_REG(__gx->peZMode);
		GX_LOAD_BP_REG(__gx->peCMode0);
	}
	if(clflag) GX_LOAD_BP_REG(__gx->peCntrl);
}