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
typedef  int u16 ;
struct __gx_litobj {int /*<<< orphan*/  nz; int /*<<< orphan*/  ny; int /*<<< orphan*/  nx; int /*<<< orphan*/  pz; int /*<<< orphan*/  py; int /*<<< orphan*/  px; int /*<<< orphan*/  k2; int /*<<< orphan*/  k1; int /*<<< orphan*/  k0; int /*<<< orphan*/  a2; int /*<<< orphan*/  a1; int /*<<< orphan*/  a0; scalar_t__ col; } ;
struct TYPE_2__ {int /*<<< orphan*/  F32; scalar_t__ U32; } ;
typedef  int /*<<< orphan*/  GXLightObj ;

/* Variables and functions */
#define  GX_LIGHT0 135 
#define  GX_LIGHT1 134 
#define  GX_LIGHT2 133 
#define  GX_LIGHT3 132 
#define  GX_LIGHT4 131 
#define  GX_LIGHT5 130 
#define  GX_LIGHT6 129 
#define  GX_LIGHT7 128 
 int /*<<< orphan*/  GX_LOAD_XF_REGS (int,int) ; 
 int _SHIFTL (int,int,int) ; 
 TYPE_1__* wgPipe ; 

void GX_LoadLightObj(GXLightObj *lit_obj,u8 lit_id)
{
	u32 id;
	u16 reg;
	struct __gx_litobj *lit = (struct __gx_litobj*)lit_obj;

	switch(lit_id) {
		case GX_LIGHT0:
			id = 0;
			break;
		case GX_LIGHT1:
			id = 1;
			break;
		case GX_LIGHT2:
			id = 2;
			break;
		case GX_LIGHT3:
			id = 3;
			break;
		case GX_LIGHT4:
			id = 4;
			break;
		case GX_LIGHT5:
			id = 5;
			break;
		case GX_LIGHT6:
			id = 6;
			break;
		case GX_LIGHT7:
			id = 7;
			break;
		default:
			id = 0;
			break;
	}

	reg = 0x600|(_SHIFTL(id,4,8));
	GX_LOAD_XF_REGS(reg,16);
	wgPipe->U32 = 0;
	wgPipe->U32 = 0;
	wgPipe->U32 = 0;
	wgPipe->U32 = lit->col;
	wgPipe->F32 = lit->a0;
	wgPipe->F32 = lit->a1;
	wgPipe->F32 = lit->a2;
	wgPipe->F32 = lit->k0;
	wgPipe->F32 = lit->k1;
	wgPipe->F32 = lit->k2;
	wgPipe->F32 = lit->px;
	wgPipe->F32 = lit->py;
	wgPipe->F32 = lit->pz;
	wgPipe->F32 = lit->nx;
	wgPipe->F32 = lit->ny;
	wgPipe->F32 = lit->nz;
}