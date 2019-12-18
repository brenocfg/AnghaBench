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
typedef  void* u32 ;
struct TYPE_2__ {int perf0Mode; int perf1Mode; int cpPerfMode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int /*<<< orphan*/  GX_LOAD_CP_REG (int,int) ; 
 int /*<<< orphan*/  GX_LOAD_XF_REG (int,int) ; 
#define  GX_PERF0_AVG_QUAD_CNT 186 
#define  GX_PERF0_CLIP_CLKS 185 
#define  GX_PERF0_CLIP_RATIO 184 
#define  GX_PERF0_CLIP_VTX 183 
#define  GX_PERF0_CLOCKS 182 
#define  GX_PERF0_NONE 181 
#define  GX_PERF0_QUAD_0CVG 180 
#define  GX_PERF0_QUAD_1CVG 179 
#define  GX_PERF0_QUAD_2CVG 178 
#define  GX_PERF0_QUAD_3CVG 177 
#define  GX_PERF0_QUAD_4CVG 176 
#define  GX_PERF0_QUAD_NON0CVG 175 
#define  GX_PERF0_TRIANGLES 174 
#define  GX_PERF0_TRIANGLES_0CLR 173 
#define  GX_PERF0_TRIANGLES_0TEX 172 
#define  GX_PERF0_TRIANGLES_1CLR 171 
#define  GX_PERF0_TRIANGLES_1TEX 170 
#define  GX_PERF0_TRIANGLES_2CLR 169 
#define  GX_PERF0_TRIANGLES_2TEX 168 
#define  GX_PERF0_TRIANGLES_3TEX 167 
#define  GX_PERF0_TRIANGLES_4TEX 166 
#define  GX_PERF0_TRIANGLES_5TEX 165 
#define  GX_PERF0_TRIANGLES_6TEX 164 
#define  GX_PERF0_TRIANGLES_7TEX 163 
#define  GX_PERF0_TRIANGLES_8TEX 162 
#define  GX_PERF0_TRIANGLES_CULLED 161 
#define  GX_PERF0_TRIANGLES_PASSED 160 
#define  GX_PERF0_TRIANGLES_SCISSORED 159 
#define  GX_PERF0_VERTICES 158 
#define  GX_PERF0_XF_BOT_CLKS 157 
#define  GX_PERF0_XF_LIT_CLKS 156 
#define  GX_PERF0_XF_REGLD_CLKS 155 
#define  GX_PERF0_XF_REGRD_CLKS 154 
#define  GX_PERF0_XF_WAIT_IN 153 
#define  GX_PERF0_XF_WAIT_OUT 152 
#define  GX_PERF0_XF_XFRM_CLKS 151 
#define  GX_PERF1_CALL_REQ 150 
#define  GX_PERF1_CLOCKS 149 
#define  GX_PERF1_CP_ALL_REQ 148 
#define  GX_PERF1_FIFO_REQ 147 
#define  GX_PERF1_NONE 146 
#define  GX_PERF1_TC_CHECK1_2 145 
#define  GX_PERF1_TC_CHECK3_4 144 
#define  GX_PERF1_TC_CHECK5_6 143 
#define  GX_PERF1_TC_CHECK7_8 142 
#define  GX_PERF1_TC_MISS 141 
#define  GX_PERF1_TEXELS 140 
#define  GX_PERF1_TX_IDLE 139 
#define  GX_PERF1_TX_MEMSTALL 138 
#define  GX_PERF1_TX_REGS 137 
#define  GX_PERF1_VC_ALL_STALLS 136 
#define  GX_PERF1_VC_ELEMQ_FULL 135 
#define  GX_PERF1_VC_MEMREQ_FULL 134 
#define  GX_PERF1_VC_MISSQ_FULL 133 
#define  GX_PERF1_VC_MISSREP_FULL 132 
#define  GX_PERF1_VC_MISS_REQ 131 
#define  GX_PERF1_VC_STATUS7 130 
#define  GX_PERF1_VC_STREAMBUF_LOW 129 
#define  GX_PERF1_VERTICES 128 
 TYPE_1__* __gx ; 
 int* _cpReg ; 

void GX_SetGPMetric(u32 perf0,u32 perf1)
{
	// check last setted perf0 counters
	if(__gx->perf0Mode>=GX_PERF0_TRIANGLES && __gx->perf0Mode<GX_PERF0_QUAD_0CVG)
		GX_LOAD_BP_REG(0x23000000);
	else if(__gx->perf0Mode>=GX_PERF0_QUAD_0CVG && __gx->perf0Mode<GX_PERF0_CLOCKS)
		GX_LOAD_BP_REG(0x24000000);
	else if(__gx->perf0Mode>=GX_PERF0_VERTICES && __gx->perf0Mode<=GX_PERF0_CLOCKS)
		GX_LOAD_XF_REG(0x1006,0);

	// check last setted perf1 counters
	if(__gx->perf1Mode>=GX_PERF1_VC_ELEMQ_FULL && __gx->perf1Mode<GX_PERF1_FIFO_REQ) {
		__gx->cpPerfMode = (__gx->cpPerfMode&~0xf0);
		GX_LOAD_CP_REG(0x20,__gx->cpPerfMode);
	} else if(__gx->perf1Mode>=GX_PERF1_FIFO_REQ && __gx->perf1Mode<GX_PERF1_CLOCKS) {
		_cpReg[3] = 0;
	} else if(__gx->perf1Mode>=GX_PERF1_TEXELS && __gx->perf1Mode<=GX_PERF1_CLOCKS) {
		GX_LOAD_BP_REG(0x67000000);
	}

	__gx->perf0Mode = perf0;
	switch(__gx->perf0Mode) {
		case GX_PERF0_CLOCKS:
			GX_LOAD_XF_REG(0x1006,0x00000273);
			break;
		case GX_PERF0_VERTICES:
			GX_LOAD_XF_REG(0x1006,0x0000014a);
			break;
		case GX_PERF0_CLIP_VTX:
			GX_LOAD_XF_REG(0x1006,0x0000016b);
			break;
		case GX_PERF0_CLIP_CLKS:
			GX_LOAD_XF_REG(0x1006,0x00000084);
			break;
		case GX_PERF0_XF_WAIT_IN:
			GX_LOAD_XF_REG(0x1006,0x000000c6);
			break;
		case GX_PERF0_XF_WAIT_OUT:
			GX_LOAD_XF_REG(0x1006,0x00000210);
			break;
		case GX_PERF0_XF_XFRM_CLKS:
			GX_LOAD_XF_REG(0x1006,0x00000252);
			break;
		case GX_PERF0_XF_LIT_CLKS:
			GX_LOAD_XF_REG(0x1006,0x00000231);
			break;
		case GX_PERF0_XF_BOT_CLKS:
			GX_LOAD_XF_REG(0x1006,0x000001ad);
			break;
		case GX_PERF0_XF_REGLD_CLKS:
			GX_LOAD_XF_REG(0x1006,0x000001ce);
			break;
		case GX_PERF0_XF_REGRD_CLKS:
			GX_LOAD_XF_REG(0x1006,0x00000021);
			break;
		case GX_PERF0_CLIP_RATIO:
			GX_LOAD_XF_REG(0x1006,0x00000153);
			break;
		case GX_PERF0_TRIANGLES:
			GX_LOAD_BP_REG(0x2300AE7F);
			break;
		case GX_PERF0_TRIANGLES_CULLED:
			GX_LOAD_BP_REG(0x23008E7F);
			break;
		case GX_PERF0_TRIANGLES_PASSED:
			GX_LOAD_BP_REG(0x23009E7F);
			break;
		case GX_PERF0_TRIANGLES_SCISSORED:
			GX_LOAD_BP_REG(0x23001E7F);
			break;
		case GX_PERF0_TRIANGLES_0TEX:
			GX_LOAD_BP_REG(0x2300AC3F);
			break;
		case GX_PERF0_TRIANGLES_1TEX:
			GX_LOAD_BP_REG(0x2300AC7F);
			break;
		case GX_PERF0_TRIANGLES_2TEX:
			GX_LOAD_BP_REG(0x2300ACBF);
			break;
		case GX_PERF0_TRIANGLES_3TEX:
			GX_LOAD_BP_REG(0x2300ACFF);
			break;
		case GX_PERF0_TRIANGLES_4TEX:
			GX_LOAD_BP_REG(0x2300AD3F);
			break;
		case GX_PERF0_TRIANGLES_5TEX:
			GX_LOAD_BP_REG(0x2300AD7F);
			break;
		case GX_PERF0_TRIANGLES_6TEX:
			GX_LOAD_BP_REG(0x2300ADBF);
			break;
		case GX_PERF0_TRIANGLES_7TEX:
			GX_LOAD_BP_REG(0x2300ADFF);
			break;
		case GX_PERF0_TRIANGLES_8TEX:
			GX_LOAD_BP_REG(0x2300AE3F);
			break;
		case GX_PERF0_TRIANGLES_0CLR:
			GX_LOAD_BP_REG(0x2300A27F);
			break;
		case GX_PERF0_TRIANGLES_1CLR:
			GX_LOAD_BP_REG(0x2300A67F);
			break;
		case GX_PERF0_TRIANGLES_2CLR:
			GX_LOAD_BP_REG(0x2300AA7F);
			break;
		case GX_PERF0_QUAD_0CVG:
			GX_LOAD_BP_REG(0x2402C0C6);
			break;
		case GX_PERF0_QUAD_NON0CVG:
			GX_LOAD_BP_REG(0x2402C16B);
			break;
		case GX_PERF0_QUAD_1CVG:
			GX_LOAD_BP_REG(0x2402C0E7);
			break;
		case GX_PERF0_QUAD_2CVG:
			GX_LOAD_BP_REG(0x2402C108);
			break;
		case GX_PERF0_QUAD_3CVG:
			GX_LOAD_BP_REG(0x2402C129);
			break;
		case GX_PERF0_QUAD_4CVG:
			GX_LOAD_BP_REG(0x2402C14A);
			break;
		case GX_PERF0_AVG_QUAD_CNT:
			GX_LOAD_BP_REG(0x2402C1AD);
			break;
		case GX_PERF0_NONE:
			break;
	}

	__gx->perf1Mode = perf1;
	switch(__gx->perf1Mode) {
		case GX_PERF1_CLOCKS:
			GX_LOAD_BP_REG(0x67000042);
			break;
		case GX_PERF1_TEXELS:
			GX_LOAD_BP_REG(0x67000084);
			break;
		case GX_PERF1_TX_IDLE:
			GX_LOAD_BP_REG(0x67000063);
			break;
		case GX_PERF1_TX_REGS:
			GX_LOAD_BP_REG(0x67000129);
			break;
		case GX_PERF1_TX_MEMSTALL:
			GX_LOAD_BP_REG(0x67000252);
			break;
		case GX_PERF1_TC_CHECK1_2:
			GX_LOAD_BP_REG(0x67000021);
			break;
		case GX_PERF1_TC_CHECK3_4:
			GX_LOAD_BP_REG(0x6700014b);
			break;
		case GX_PERF1_TC_CHECK5_6:
			GX_LOAD_BP_REG(0x6700018d);
			break;
		case GX_PERF1_TC_CHECK7_8:
			GX_LOAD_BP_REG(0x670001cf);
			break;
		case GX_PERF1_TC_MISS:
			GX_LOAD_BP_REG(0x67000211);
			break;
		case GX_PERF1_VC_ELEMQ_FULL:
			__gx->cpPerfMode = (__gx->cpPerfMode&~0xf0)|0x20;
			GX_LOAD_CP_REG(0x20,__gx->cpPerfMode);
			break;
		case GX_PERF1_VC_MISSQ_FULL:
			__gx->cpPerfMode = (__gx->cpPerfMode&~0xf0)|0x30;
			GX_LOAD_CP_REG(0x20,__gx->cpPerfMode);
			break;
		case GX_PERF1_VC_MEMREQ_FULL:
			__gx->cpPerfMode = (__gx->cpPerfMode&~0xf0)|0x40;
			GX_LOAD_CP_REG(0x20,__gx->cpPerfMode);
			break;
		case GX_PERF1_VC_STATUS7:
			__gx->cpPerfMode = (__gx->cpPerfMode&~0xf0)|0x50;
			GX_LOAD_CP_REG(0x20,__gx->cpPerfMode);
			break;
		case GX_PERF1_VC_MISSREP_FULL:
			__gx->cpPerfMode = (__gx->cpPerfMode&~0xf0)|0x60;
			GX_LOAD_CP_REG(0x20,__gx->cpPerfMode);
			break;
		case GX_PERF1_VC_STREAMBUF_LOW:
			__gx->cpPerfMode = (__gx->cpPerfMode&~0xf0)|0x70;
			GX_LOAD_CP_REG(0x20,__gx->cpPerfMode);
			break;
		case GX_PERF1_VC_ALL_STALLS:
			__gx->cpPerfMode = (__gx->cpPerfMode&~0xf0)|0x90;
			GX_LOAD_CP_REG(0x20,__gx->cpPerfMode);
			break;
		case GX_PERF1_VERTICES:
			__gx->cpPerfMode = (__gx->cpPerfMode&~0xf0)|0x80;
			GX_LOAD_CP_REG(0x20,__gx->cpPerfMode);
			break;
		case GX_PERF1_FIFO_REQ:
			_cpReg[3] = 2;
			break;
		case GX_PERF1_CALL_REQ:
			_cpReg[3] = 3;
			break;
		case GX_PERF1_VC_MISS_REQ:
			_cpReg[3] = 4;
			break;
		case GX_PERF1_CP_ALL_REQ:
			_cpReg[3] = 5;
			break;
		case GX_PERF1_NONE:
			break;
	}

}