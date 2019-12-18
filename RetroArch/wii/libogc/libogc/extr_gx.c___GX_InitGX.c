#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ s32 ;
struct TYPE_14__ {int viHeight; int xfbHeight; int /*<<< orphan*/  efbHeight; int /*<<< orphan*/  fbWidth; int /*<<< orphan*/  field_rendering; } ;
struct TYPE_12__ {int member_2; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int member_1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int member_0; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_13__ {TYPE_3__ member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_4__ Mtx ;
typedef  TYPE_5__ GXRModeObj ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 scalar_t__ BLACK ; 
 int /*<<< orphan*/  GX_AF_NONE ; 
 int /*<<< orphan*/  GX_ALWAYS ; 
 int /*<<< orphan*/  GX_AOP_AND ; 
 int /*<<< orphan*/  GX_BL_INVSRCALPHA ; 
 int /*<<< orphan*/  GX_BL_ONE ; 
 int /*<<< orphan*/  GX_BL_SRCALPHA ; 
 int /*<<< orphan*/  GX_BL_ZERO ; 
 int /*<<< orphan*/  GX_BM_NONE ; 
 int /*<<< orphan*/  GX_CH_ALPHA ; 
 int /*<<< orphan*/  GX_CH_BLUE ; 
 int /*<<< orphan*/  GX_CH_GREEN ; 
 int /*<<< orphan*/  GX_CH_RED ; 
 int GX_CLAMP_BOTTOM ; 
 int GX_CLAMP_TOP ; 
 int /*<<< orphan*/  GX_CLIP_ENABLE ; 
 int /*<<< orphan*/  GX_COLOR0A0 ; 
 int /*<<< orphan*/  GX_COLOR1A1 ; 
 int /*<<< orphan*/  GX_COLORNULL ; 
 int /*<<< orphan*/  GX_COPY_PROGRESSIVE ; 
 int /*<<< orphan*/  GX_CULL_BACK ; 
 int /*<<< orphan*/  GX_ClearBoundingBox () ; 
 int /*<<< orphan*/  GX_ClearGPMetric () ; 
 int /*<<< orphan*/  GX_ClearVtxDesc () ; 
 scalar_t__ GX_DEFAULT_BG ; 
 int /*<<< orphan*/  GX_DF_NONE ; 
 int /*<<< orphan*/  GX_DISABLE ; 
 int /*<<< orphan*/  GX_DTTIDENTITY ; 
 int /*<<< orphan*/  GX_ENABLE ; 
 int /*<<< orphan*/  GX_EnableTexOffsets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_FOG_NONE ; 
 int /*<<< orphan*/  GX_GM_1_0 ; 
 int /*<<< orphan*/  GX_IDENTITY ; 
 int /*<<< orphan*/  GX_INDTEXSTAGE0 ; 
 int /*<<< orphan*/  GX_INDTEXSTAGE1 ; 
 int /*<<< orphan*/  GX_INDTEXSTAGE2 ; 
 int /*<<< orphan*/  GX_INDTEXSTAGE3 ; 
 int /*<<< orphan*/  GX_ITS_1 ; 
 int /*<<< orphan*/  GX_InvVtxCache () ; 
 int /*<<< orphan*/  GX_InvalidateTexAll () ; 
 int /*<<< orphan*/  GX_LEQUAL ; 
 int /*<<< orphan*/  GX_LIGHTNULL ; 
 int /*<<< orphan*/  GX_LO_CLEAR ; 
 int /*<<< orphan*/  GX_LO_SET ; 
 int /*<<< orphan*/  GX_LoadNrmMtxImm (TYPE_4__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_LoadPosMtxImm (TYPE_4__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_LoadTexMtxImm (TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GX_MAX_TEVSTAGE ; 
 int /*<<< orphan*/  GX_MTX3x4 ; 
 int /*<<< orphan*/  GX_PERF0_NONE ; 
 int /*<<< orphan*/  GX_PERF1_NONE ; 
 int /*<<< orphan*/  GX_PF_RGB8_Z24 ; 
 int /*<<< orphan*/  GX_PNMTX0 ; 
 int /*<<< orphan*/  GX_PokeAlphaMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_PokeAlphaRead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_PokeAlphaUpdate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_PokeBlendMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_PokeColorUpdate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_PokeDither (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_PokeDstAlpha (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_PokeZMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_READ_FF ; 
 int /*<<< orphan*/  GX_REPLACE ; 
 int /*<<< orphan*/  GX_SRC_REG ; 
 int /*<<< orphan*/  GX_SRC_VTX ; 
 int /*<<< orphan*/  GX_SetAlphaCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetAlphaUpdate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetBlendMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetChanAmbColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetChanCtrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetChanMatColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetClipMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetCoPlanar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetColorUpdate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetCopyClamp (int) ; 
 int /*<<< orphan*/  GX_SetCopyClear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_SetCopyFilter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GX_SetCullMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetCurrentMtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetDispCopyDst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetDispCopyFrame2Field (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetDispCopyGamma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetDispCopySrc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetDispCopyYScale (double) ; 
 int /*<<< orphan*/  GX_SetDither (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetDstAlpha (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetFieldMask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetFieldMode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_SetFog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetFogRangeAdj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GX_SetGPMetric (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetIndTexCoordScale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetLineWidth (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetNumChans (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetNumIndStages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetNumTevStages (int) ; 
 int /*<<< orphan*/  GX_SetNumTexGens (int) ; 
 int /*<<< orphan*/  GX_SetPixelFmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetPointSize (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetScissor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetScissorBoxOffset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTevDirect (scalar_t__) ; 
 int /*<<< orphan*/  GX_SetTevKAlphaSel (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTevKColorSel (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTevOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTevOrder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTevSwapMode (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTevSwapModeTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTexCoordGen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTexRegionCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTlutRegionCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_SetZCompLoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetZMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetZTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_TEVSTAGE0 ; 
 int /*<<< orphan*/  GX_TEVSTAGE1 ; 
 int /*<<< orphan*/  GX_TEVSTAGE10 ; 
 int /*<<< orphan*/  GX_TEVSTAGE11 ; 
 int /*<<< orphan*/  GX_TEVSTAGE12 ; 
 int /*<<< orphan*/  GX_TEVSTAGE13 ; 
 int /*<<< orphan*/  GX_TEVSTAGE14 ; 
 int /*<<< orphan*/  GX_TEVSTAGE15 ; 
 int /*<<< orphan*/  GX_TEVSTAGE2 ; 
 int /*<<< orphan*/  GX_TEVSTAGE3 ; 
 int /*<<< orphan*/  GX_TEVSTAGE4 ; 
 int /*<<< orphan*/  GX_TEVSTAGE5 ; 
 int /*<<< orphan*/  GX_TEVSTAGE6 ; 
 int /*<<< orphan*/  GX_TEVSTAGE7 ; 
 int /*<<< orphan*/  GX_TEVSTAGE8 ; 
 int /*<<< orphan*/  GX_TEVSTAGE9 ; 
 int /*<<< orphan*/  GX_TEV_KASEL_1 ; 
 int /*<<< orphan*/  GX_TEV_KCSEL_1_4 ; 
 int /*<<< orphan*/  GX_TEV_SWAP0 ; 
 int /*<<< orphan*/  GX_TEV_SWAP1 ; 
 int /*<<< orphan*/  GX_TEV_SWAP2 ; 
 int /*<<< orphan*/  GX_TEV_SWAP3 ; 
 int /*<<< orphan*/  GX_TEXCOORD0 ; 
 int /*<<< orphan*/  GX_TEXCOORD1 ; 
 int /*<<< orphan*/  GX_TEXCOORD2 ; 
 int /*<<< orphan*/  GX_TEXCOORD3 ; 
 int /*<<< orphan*/  GX_TEXCOORD4 ; 
 int /*<<< orphan*/  GX_TEXCOORD5 ; 
 int /*<<< orphan*/  GX_TEXCOORD6 ; 
 int /*<<< orphan*/  GX_TEXCOORD7 ; 
 int /*<<< orphan*/  GX_TEXCOORDNULL ; 
 int /*<<< orphan*/  GX_TEXMAP0 ; 
 int /*<<< orphan*/  GX_TEXMAP1 ; 
 int /*<<< orphan*/  GX_TEXMAP2 ; 
 int /*<<< orphan*/  GX_TEXMAP3 ; 
 int /*<<< orphan*/  GX_TEXMAP4 ; 
 int /*<<< orphan*/  GX_TEXMAP5 ; 
 int /*<<< orphan*/  GX_TEXMAP6 ; 
 int /*<<< orphan*/  GX_TEXMAP7 ; 
 int /*<<< orphan*/  GX_TEXMAP_NULL ; 
 int /*<<< orphan*/  GX_TF_Z8 ; 
 int /*<<< orphan*/  GX_TG_MTX2x4 ; 
 int /*<<< orphan*/  GX_TG_TEX0 ; 
 int /*<<< orphan*/  GX_TG_TEX1 ; 
 int /*<<< orphan*/  GX_TG_TEX2 ; 
 int /*<<< orphan*/  GX_TG_TEX3 ; 
 int /*<<< orphan*/  GX_TG_TEX4 ; 
 int /*<<< orphan*/  GX_TG_TEX5 ; 
 int /*<<< orphan*/  GX_TG_TEX6 ; 
 int /*<<< orphan*/  GX_TG_TEX7 ; 
 int /*<<< orphan*/  GX_TO_ZERO ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int /*<<< orphan*/  GX_ZC_LINEAR ; 
 int /*<<< orphan*/  GX_ZT_DISABLE ; 
 TYPE_5__* VIDEO_GetPreferredMode (int /*<<< orphan*/ *) ; 
 scalar_t__ WHITE ; 
 int /*<<< orphan*/  __GXDefTexRegionCallback ; 
 int /*<<< orphan*/  __GXDefTlutRegionCallback ; 

__attribute__((used)) static void __GX_InitGX()
{
	s32 i;
	u32 flag;
	GXRModeObj *rmode;
	Mtx identity_matrix =
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0}
	};

	rmode = VIDEO_GetPreferredMode(NULL);

	GX_SetCopyClear((GXColor)BLACK,0xffffff);
	GX_SetTexCoordGen(GX_TEXCOORD0,GX_TG_MTX2x4,GX_TG_TEX0,GX_IDENTITY);
	GX_SetTexCoordGen(GX_TEXCOORD1,GX_TG_MTX2x4,GX_TG_TEX1,GX_IDENTITY);
	GX_SetTexCoordGen(GX_TEXCOORD2,GX_TG_MTX2x4,GX_TG_TEX2,GX_IDENTITY);
	GX_SetTexCoordGen(GX_TEXCOORD3,GX_TG_MTX2x4,GX_TG_TEX3,GX_IDENTITY);
	GX_SetTexCoordGen(GX_TEXCOORD4,GX_TG_MTX2x4,GX_TG_TEX4,GX_IDENTITY);
	GX_SetTexCoordGen(GX_TEXCOORD5,GX_TG_MTX2x4,GX_TG_TEX5,GX_IDENTITY);
	GX_SetTexCoordGen(GX_TEXCOORD6,GX_TG_MTX2x4,GX_TG_TEX6,GX_IDENTITY);
	GX_SetTexCoordGen(GX_TEXCOORD7,GX_TG_MTX2x4,GX_TG_TEX7,GX_IDENTITY);
	GX_SetNumTexGens(1);
	GX_ClearVtxDesc();
	GX_InvVtxCache();

	GX_SetLineWidth(6,GX_TO_ZERO);
	GX_SetPointSize(6,GX_TO_ZERO);

	GX_EnableTexOffsets(GX_TEXCOORD0,GX_DISABLE,GX_DISABLE);
	GX_EnableTexOffsets(GX_TEXCOORD1,GX_DISABLE,GX_DISABLE);
	GX_EnableTexOffsets(GX_TEXCOORD2,GX_DISABLE,GX_DISABLE);
	GX_EnableTexOffsets(GX_TEXCOORD3,GX_DISABLE,GX_DISABLE);
	GX_EnableTexOffsets(GX_TEXCOORD4,GX_DISABLE,GX_DISABLE);
	GX_EnableTexOffsets(GX_TEXCOORD5,GX_DISABLE,GX_DISABLE);
	GX_EnableTexOffsets(GX_TEXCOORD6,GX_DISABLE,GX_DISABLE);
	GX_EnableTexOffsets(GX_TEXCOORD7,GX_DISABLE,GX_DISABLE);

	GX_LoadPosMtxImm(identity_matrix,GX_PNMTX0);
	GX_LoadNrmMtxImm(identity_matrix,GX_PNMTX0);
	GX_SetCurrentMtx(GX_PNMTX0);
	GX_LoadTexMtxImm(identity_matrix,GX_IDENTITY,GX_MTX3x4);
	GX_LoadTexMtxImm(identity_matrix,GX_DTTIDENTITY,GX_MTX3x4);

	GX_SetViewport(0,0,rmode->fbWidth,rmode->efbHeight,0,1);
	GX_SetCoPlanar(GX_DISABLE);
	GX_SetCullMode(GX_CULL_BACK);
	GX_SetClipMode(GX_CLIP_ENABLE);

	GX_SetScissor(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetScissorBoxOffset(0,0);

	GX_SetNumChans(0);

	GX_SetChanCtrl(GX_COLOR0A0,GX_DISABLE,GX_SRC_REG,GX_SRC_VTX,GX_LIGHTNULL,GX_DF_NONE,GX_AF_NONE);
	GX_SetChanAmbColor(GX_COLOR0A0,(GXColor)BLACK);
	GX_SetChanMatColor(GX_COLOR0A0,(GXColor)WHITE);

	GX_SetChanCtrl(GX_COLOR1A1,GX_DISABLE,GX_SRC_REG,GX_SRC_VTX,GX_LIGHTNULL,GX_DF_NONE,GX_AF_NONE);
	GX_SetChanAmbColor(GX_COLOR1A1,(GXColor)BLACK);
	GX_SetChanMatColor(GX_COLOR1A1,(GXColor)WHITE);

	GX_InvalidateTexAll();
	GX_SetTexRegionCallback(__GXDefTexRegionCallback);
	GX_SetTlutRegionCallback(__GXDefTlutRegionCallback);

	GX_SetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,GX_TEXMAP0,GX_COLOR0A0);
	GX_SetTevOrder(GX_TEVSTAGE1,GX_TEXCOORD1,GX_TEXMAP1,GX_COLOR0A0);
	GX_SetTevOrder(GX_TEVSTAGE2,GX_TEXCOORD2,GX_TEXMAP2,GX_COLOR0A0);
	GX_SetTevOrder(GX_TEVSTAGE3,GX_TEXCOORD3,GX_TEXMAP3,GX_COLOR0A0);
	GX_SetTevOrder(GX_TEVSTAGE4,GX_TEXCOORD4,GX_TEXMAP4,GX_COLOR0A0);
	GX_SetTevOrder(GX_TEVSTAGE5,GX_TEXCOORD5,GX_TEXMAP5,GX_COLOR0A0);
	GX_SetTevOrder(GX_TEVSTAGE6,GX_TEXCOORD6,GX_TEXMAP6,GX_COLOR0A0);
	GX_SetTevOrder(GX_TEVSTAGE7,GX_TEXCOORD7,GX_TEXMAP7,GX_COLOR0A0);
	GX_SetTevOrder(GX_TEVSTAGE8,GX_TEXCOORDNULL,GX_TEXMAP_NULL,GX_COLORNULL);
	GX_SetTevOrder(GX_TEVSTAGE9,GX_TEXCOORDNULL,GX_TEXMAP_NULL,GX_COLORNULL);
	GX_SetTevOrder(GX_TEVSTAGE10,GX_TEXCOORDNULL,GX_TEXMAP_NULL,GX_COLORNULL);
	GX_SetTevOrder(GX_TEVSTAGE11,GX_TEXCOORDNULL,GX_TEXMAP_NULL,GX_COLORNULL);
	GX_SetTevOrder(GX_TEVSTAGE12,GX_TEXCOORDNULL,GX_TEXMAP_NULL,GX_COLORNULL);
	GX_SetTevOrder(GX_TEVSTAGE13,GX_TEXCOORDNULL,GX_TEXMAP_NULL,GX_COLORNULL);
	GX_SetTevOrder(GX_TEVSTAGE14,GX_TEXCOORDNULL,GX_TEXMAP_NULL,GX_COLORNULL);
	GX_SetTevOrder(GX_TEVSTAGE15,GX_TEXCOORDNULL,GX_TEXMAP_NULL,GX_COLORNULL);
	GX_SetNumTevStages(1);
	GX_SetTevOp(GX_TEVSTAGE0,GX_REPLACE);
	GX_SetAlphaCompare(GX_ALWAYS,0,GX_AOP_AND,GX_ALWAYS,0);
	GX_SetZTexture(GX_ZT_DISABLE,GX_TF_Z8,0);
	for(i=0;i<GX_MAX_TEVSTAGE;i++) {
		GX_SetTevKColorSel(i,GX_TEV_KCSEL_1_4);
		GX_SetTevKAlphaSel(i,GX_TEV_KASEL_1);
		GX_SetTevSwapMode(i,GX_TEV_SWAP0,GX_TEV_SWAP0);
	}

	GX_SetTevSwapModeTable(GX_TEV_SWAP0,GX_CH_RED,GX_CH_GREEN,GX_CH_BLUE,GX_CH_ALPHA);
	GX_SetTevSwapModeTable(GX_TEV_SWAP1,GX_CH_RED,GX_CH_RED,GX_CH_RED,GX_CH_ALPHA);
	GX_SetTevSwapModeTable(GX_TEV_SWAP2,GX_CH_GREEN,GX_CH_GREEN,GX_CH_GREEN,GX_CH_ALPHA);
	GX_SetTevSwapModeTable(GX_TEV_SWAP3,GX_CH_BLUE,GX_CH_BLUE,GX_CH_BLUE,GX_CH_ALPHA);
	for(i=0;i<GX_MAX_TEVSTAGE;i++) {
		GX_SetTevDirect(i);
	}

	GX_SetNumIndStages(0);
	GX_SetIndTexCoordScale(GX_INDTEXSTAGE0,GX_ITS_1,GX_ITS_1);
	GX_SetIndTexCoordScale(GX_INDTEXSTAGE1,GX_ITS_1,GX_ITS_1);
	GX_SetIndTexCoordScale(GX_INDTEXSTAGE2,GX_ITS_1,GX_ITS_1);
	GX_SetIndTexCoordScale(GX_INDTEXSTAGE3,GX_ITS_1,GX_ITS_1);

	GX_SetFog(GX_FOG_NONE,0,1,0.1,1,(GXColor)BLACK);
	GX_SetFogRangeAdj(GX_DISABLE,0,NULL);

	GX_SetBlendMode(GX_BM_NONE,GX_BL_SRCALPHA,GX_BL_INVSRCALPHA,GX_LO_CLEAR);
	GX_SetColorUpdate(GX_ENABLE);
	GX_SetAlphaUpdate(GX_ENABLE);
	GX_SetZMode(GX_ENABLE,GX_LEQUAL,GX_TRUE);
	GX_SetZCompLoc(GX_TRUE);
	GX_SetDither(GX_ENABLE);
	GX_SetDstAlpha(GX_DISABLE,0);
	GX_SetPixelFmt(GX_PF_RGB8_Z24,GX_ZC_LINEAR);

	GX_SetFieldMask(GX_ENABLE,GX_ENABLE);

	flag = 0;
	if(rmode->viHeight==(rmode->xfbHeight<<1)) flag = 1;
	GX_SetFieldMode(rmode->field_rendering,flag);

	GX_SetCopyClear((GXColor)GX_DEFAULT_BG,0x00ffffff);
	GX_SetDispCopySrc(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopyDst(rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopyYScale(1.0);
	GX_SetCopyClamp(GX_CLAMP_TOP|GX_CLAMP_BOTTOM);
	GX_SetCopyFilter(GX_FALSE,NULL,GX_FALSE,NULL);
	GX_SetDispCopyGamma(GX_GM_1_0);
	GX_SetDispCopyFrame2Field(GX_COPY_PROGRESSIVE);
	GX_ClearBoundingBox();

	GX_PokeColorUpdate(GX_TRUE);
	GX_PokeAlphaUpdate(GX_TRUE);
	GX_PokeDither(GX_FALSE);
	GX_PokeBlendMode(GX_BM_NONE,GX_BL_ZERO,GX_BL_ONE,GX_LO_SET);
	GX_PokeAlphaMode(GX_ALWAYS,0);
	GX_PokeAlphaRead(GX_READ_FF);
	GX_PokeDstAlpha(GX_DISABLE,0);
	GX_PokeZMode(GX_TRUE,GX_ALWAYS,GX_TRUE);

	GX_SetGPMetric(GX_PERF0_NONE,GX_PERF1_NONE);
	GX_ClearGPMetric();
}