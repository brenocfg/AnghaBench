#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int,int) ;} ;
typedef  TYPE_1__ refimport_t ;
struct TYPE_8__ {int /*<<< orphan*/  inPVS; int /*<<< orphan*/  GetEntityToken; int /*<<< orphan*/  RemapShader; int /*<<< orphan*/  RegisterFont; int /*<<< orphan*/  UploadCinematic; int /*<<< orphan*/  DrawStretchRaw; int /*<<< orphan*/  DrawStretchPic; int /*<<< orphan*/  SetColor; int /*<<< orphan*/  RenderScene; int /*<<< orphan*/  AddAdditiveLightToScene; int /*<<< orphan*/  AddLightToScene; int /*<<< orphan*/  LightForPoint; int /*<<< orphan*/  AddPolyToScene; int /*<<< orphan*/  AddRefEntityToScene; int /*<<< orphan*/  ClearScene; int /*<<< orphan*/  ModelBounds; int /*<<< orphan*/  LerpTag; int /*<<< orphan*/  MarkFragments; int /*<<< orphan*/  EndFrame; int /*<<< orphan*/  BeginFrame; int /*<<< orphan*/  EndRegistration; int /*<<< orphan*/  SetWorldVisData; int /*<<< orphan*/  LoadWorld; int /*<<< orphan*/  RegisterShaderNoMip; int /*<<< orphan*/  RegisterShader; int /*<<< orphan*/  RegisterSkin; int /*<<< orphan*/  RegisterModel; int /*<<< orphan*/  BeginRegistration; int /*<<< orphan*/  Shutdown; } ;
typedef  TYPE_2__ refexport_t ;
typedef  int /*<<< orphan*/  re ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int REF_API_VERSION ; 
 int /*<<< orphan*/  RE_AddAdditiveLightToScene ; 
 int /*<<< orphan*/  RE_AddLightToScene ; 
 int /*<<< orphan*/  RE_AddPolyToScene ; 
 int /*<<< orphan*/  RE_AddRefEntityToScene ; 
 int /*<<< orphan*/  RE_BeginFrame ; 
 int /*<<< orphan*/  RE_BeginRegistration ; 
 int /*<<< orphan*/  RE_ClearScene ; 
 int /*<<< orphan*/  RE_EndFrame ; 
 int /*<<< orphan*/  RE_EndRegistration ; 
 int /*<<< orphan*/  RE_LoadWorldMap ; 
 int /*<<< orphan*/  RE_RegisterFont ; 
 int /*<<< orphan*/  RE_RegisterModel ; 
 int /*<<< orphan*/  RE_RegisterShader ; 
 int /*<<< orphan*/  RE_RegisterShaderNoMip ; 
 int /*<<< orphan*/  RE_RegisterSkin ; 
 int /*<<< orphan*/  RE_RenderScene ; 
 int /*<<< orphan*/  RE_SetColor ; 
 int /*<<< orphan*/  RE_SetWorldVisData ; 
 int /*<<< orphan*/  RE_Shutdown ; 
 int /*<<< orphan*/  RE_StretchPic ; 
 int /*<<< orphan*/  RE_StretchRaw ; 
 int /*<<< orphan*/  RE_UploadCinematic ; 
 int /*<<< orphan*/  R_GetEntityToken ; 
 int /*<<< orphan*/  R_LerpTag ; 
 int /*<<< orphan*/  R_LightForPoint ; 
 int /*<<< orphan*/  R_MarkFragments ; 
 int /*<<< orphan*/  R_ModelBounds ; 
 int /*<<< orphan*/  R_RemapShader ; 
 int /*<<< orphan*/  R_inPVS ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int,int) ; 

refexport_t *GetRefAPI ( int apiVersion, refimport_t *rimp ) {
	static refexport_t	re;

	ri = *rimp;

	Com_Memset( &re, 0, sizeof( re ) );

	if ( apiVersion != REF_API_VERSION ) {
		ri.Printf(PRINT_ALL, "Mismatched REF_API_VERSION: expected %i, got %i\n", 
			REF_API_VERSION, apiVersion );
		return NULL;
	}

	// the RE_ functions are Renderer Entry points

	re.Shutdown = RE_Shutdown;

	re.BeginRegistration = RE_BeginRegistration;
	re.RegisterModel = RE_RegisterModel;
	re.RegisterSkin = RE_RegisterSkin;
	re.RegisterShader = RE_RegisterShader;
	re.RegisterShaderNoMip = RE_RegisterShaderNoMip;
	re.LoadWorld = RE_LoadWorldMap;
	re.SetWorldVisData = RE_SetWorldVisData;
	re.EndRegistration = RE_EndRegistration;

	re.BeginFrame = RE_BeginFrame;
	re.EndFrame = RE_EndFrame;

	re.MarkFragments = R_MarkFragments;
	re.LerpTag = R_LerpTag;
	re.ModelBounds = R_ModelBounds;

	re.ClearScene = RE_ClearScene;
	re.AddRefEntityToScene = RE_AddRefEntityToScene;
	re.AddPolyToScene = RE_AddPolyToScene;
	re.LightForPoint = R_LightForPoint;
	re.AddLightToScene = RE_AddLightToScene;
	re.AddAdditiveLightToScene = RE_AddAdditiveLightToScene;
	re.RenderScene = RE_RenderScene;

	re.SetColor = RE_SetColor;
	re.DrawStretchPic = RE_StretchPic;
	re.DrawStretchRaw = RE_StretchRaw;
	re.UploadCinematic = RE_UploadCinematic;

	re.RegisterFont = RE_RegisterFont;
	re.RemapShader = R_RemapShader;
	re.GetEntityToken = R_GetEntityToken;
	re.inPVS = R_inPVS;

	return &re;
}