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
struct TYPE_2__ {int genMode; int* tevRasOrder; int tevIndMask; } ;

/* Variables and functions */
#define  GX_INDTEXSTAGE0 131 
#define  GX_INDTEXSTAGE1 130 
#define  GX_INDTEXSTAGE2 129 
#define  GX_INDTEXSTAGE3 128 
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int _SHIFTR (int,int,int) ; 
 TYPE_1__* __gx ; 

__attribute__((used)) static void __GX_UpdateBPMask()
{
#if defined(HW_DOL)
	u32 i;
	u32 nbmp,nres;
	u8 ntexmap;

	nbmp = _SHIFTR(__gx->genMode,16,3);

	nres = 0;
	for(i=0;i<nbmp;i++) {
		switch(i) {
			case GX_INDTEXSTAGE0:
				ntexmap = __gx->tevRasOrder[2]&7;
				break;
			case GX_INDTEXSTAGE1:
				ntexmap = _SHIFTR(__gx->tevRasOrder[2],6,3);
				break;
			case GX_INDTEXSTAGE2:
				ntexmap = _SHIFTR(__gx->tevRasOrder[2],12,3);
				break;
			case GX_INDTEXSTAGE3:
				ntexmap = _SHIFTR(__gx->tevRasOrder[2],18,3);
				break;
			default:
				ntexmap = 0;
				break;
		}
		nres |= (1<<ntexmap);
	}

	if((__gx->tevIndMask&0xff)!=nres) {
		__gx->tevIndMask = (__gx->tevIndMask&~0xff)|(nres&0xff);
		GX_LOAD_BP_REG(__gx->tevIndMask);
	}
#endif
}