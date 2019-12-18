#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_17__ {double vidHeight; double vidWidth; } ;
struct TYPE_18__ {double yscale; double xscale; double bias; void* (* registerShaderNoMip ) (char*) ;scalar_t__ (* getCVarValue ) (char*) ;void* whiteShader; void* cursor; int /*<<< orphan*/ * runCinematicFrame; int /*<<< orphan*/ * drawCinematic; int /*<<< orphan*/ * stopCinematic; int /*<<< orphan*/ * playCinematic; int /*<<< orphan*/ * stopBackgroundTrack; int /*<<< orphan*/ * startBackgroundTrack; int /*<<< orphan*/ * registerSound; int /*<<< orphan*/ * ownerDrawWidth; int /*<<< orphan*/ * Pause; int /*<<< orphan*/ * Print; int /*<<< orphan*/ * Error; int /*<<< orphan*/ * executeText; int /*<<< orphan*/ * keynumToStringBuf; int /*<<< orphan*/ * getBindingBuf; int /*<<< orphan*/ * setBinding; int /*<<< orphan*/ * feederSelection; int /*<<< orphan*/ * feederItemText; int /*<<< orphan*/ * feederItemImage; int /*<<< orphan*/ * feederCount; int /*<<< orphan*/ * ownerDrawHandleKey; int /*<<< orphan*/ * startLocalSound; int /*<<< orphan*/ * getOverstrikeMode; int /*<<< orphan*/ * setOverstrikeMode; int /*<<< orphan*/ * drawTextWithCursor; int /*<<< orphan*/  getCVarString; int /*<<< orphan*/  (* setCVar ) (char*,char*) ;int /*<<< orphan*/ * getTeamColor; int /*<<< orphan*/ * runScript; int /*<<< orphan*/ * ownerDrawVisible; int /*<<< orphan*/ * getValue; int /*<<< orphan*/ * ownerDrawItem; int /*<<< orphan*/ * registerFont; int /*<<< orphan*/ * renderScene; int /*<<< orphan*/ * addRefEntityToScene; int /*<<< orphan*/ * drawSides; int /*<<< orphan*/ * clearScene; int /*<<< orphan*/ * drawTopBottom; int /*<<< orphan*/ * drawRect; int /*<<< orphan*/ * fillRect; int /*<<< orphan*/ * modelBounds; int /*<<< orphan*/ * registerModel; int /*<<< orphan*/ * textHeight; int /*<<< orphan*/ * textWidth; int /*<<< orphan*/ * drawText; int /*<<< orphan*/ * drawStretchPic; int /*<<< orphan*/ * drawHandlePic; int /*<<< orphan*/ * setColor; TYPE_8__ glconfig; } ;
struct TYPE_12__ {int currentServerCinematic; } ;
struct TYPE_16__ {int currentCrosshair; int previewMovie; TYPE_3__ serverStatus; int /*<<< orphan*/  effectsColor; TYPE_2__* gameTypes; TYPE_1__* mapList; scalar_t__ inGameLoad; scalar_t__ aliasCount; scalar_t__ characterCount; scalar_t__ teamCount; TYPE_9__ uiDC; } ;
struct TYPE_15__ {size_t integer; } ;
struct TYPE_14__ {size_t integer; } ;
struct TYPE_13__ {int /*<<< orphan*/  integer; } ;
struct TYPE_11__ {int /*<<< orphan*/  gtEnum; } ;
struct TYPE_10__ {int /*<<< orphan*/  mapLoadName; } ;

/* Variables and functions */
 int /*<<< orphan*/  AssetCache () ; 
 int /*<<< orphan*/  Com_Error ; 
 int /*<<< orphan*/  Com_Printf ; 
 int /*<<< orphan*/  Init_Display (TYPE_9__*) ; 
 int /*<<< orphan*/  Menus_CloseAll () ; 
 int /*<<< orphan*/  String_Init () ; 
 int /*<<< orphan*/  Text_Height ; 
 int /*<<< orphan*/  Text_Paint ; 
 int /*<<< orphan*/  Text_PaintWithCursor ; 
 int /*<<< orphan*/  Text_Width ; 
 int /*<<< orphan*/  UI_BuildQ3Model_List () ; 
 char* UI_Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  UI_DrawCinematic ; 
 int /*<<< orphan*/  UI_DrawHandlePic ; 
 int /*<<< orphan*/  UI_FeederCount ; 
 int /*<<< orphan*/  UI_FeederItemImage ; 
 int /*<<< orphan*/  UI_FeederItemText ; 
 int /*<<< orphan*/  UI_FeederSelection ; 
 int /*<<< orphan*/  UI_FillRect ; 
 int /*<<< orphan*/  UI_GetTeamColor ; 
 int /*<<< orphan*/  UI_GetValue ; 
 int /*<<< orphan*/  UI_InitMemory () ; 
 int /*<<< orphan*/  UI_LoadBestScores (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_LoadBots () ; 
 int /*<<< orphan*/  UI_LoadMenus (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_LoadTeams () ; 
 int /*<<< orphan*/  UI_OwnerDraw ; 
 int /*<<< orphan*/  UI_OwnerDrawHandleKey ; 
 int /*<<< orphan*/  UI_OwnerDrawVisible ; 
 int /*<<< orphan*/  UI_OwnerDrawWidth ; 
 int /*<<< orphan*/  UI_ParseGameInfo (char*) ; 
 int /*<<< orphan*/  UI_ParseTeamInfo (char*) ; 
 int /*<<< orphan*/  UI_Pause ; 
 int /*<<< orphan*/  UI_PlayCinematic ; 
 int /*<<< orphan*/  UI_RegisterCvars () ; 
 int /*<<< orphan*/  UI_RunCinematicFrame ; 
 int /*<<< orphan*/  UI_RunMenuScript ; 
 int /*<<< orphan*/  UI_SetColor ; 
 int /*<<< orphan*/  UI_StopCinematic ; 
 int /*<<< orphan*/  _UI_DrawRect ; 
 int /*<<< orphan*/  _UI_DrawSides ; 
 int /*<<< orphan*/  _UI_DrawTopBottom ; 
 int /*<<< orphan*/ * gamecodetoui ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText ; 
 int /*<<< orphan*/  trap_Cvar_Register (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  trap_GetGlconfig (TYPE_8__*) ; 
 int /*<<< orphan*/  trap_Key_GetBindingBuf ; 
 int /*<<< orphan*/  trap_Key_GetOverstrikeMode ; 
 int /*<<< orphan*/  trap_Key_KeynumToStringBuf ; 
 int /*<<< orphan*/  trap_Key_SetBinding ; 
 int /*<<< orphan*/  trap_Key_SetOverstrikeMode ; 
 int /*<<< orphan*/  trap_LAN_LoadCachedServers () ; 
 int trap_Milliseconds () ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene ; 
 int /*<<< orphan*/  trap_R_ClearScene ; 
 int /*<<< orphan*/  trap_R_DrawStretchPic ; 
 int /*<<< orphan*/  trap_R_ModelBounds ; 
 int /*<<< orphan*/  trap_R_RegisterFont ; 
 int /*<<< orphan*/  trap_R_RegisterModel ; 
 void* trap_R_RegisterShaderNoMip (char*) ; 
 int /*<<< orphan*/  trap_R_RenderScene ; 
 int /*<<< orphan*/  trap_S_RegisterSound ; 
 int /*<<< orphan*/  trap_S_StartBackgroundTrack ; 
 int /*<<< orphan*/  trap_S_StartLocalSound ; 
 int /*<<< orphan*/  trap_S_StopBackgroundTrack ; 
 TYPE_7__ uiInfo ; 
 TYPE_6__ ui_currentMap ; 
 TYPE_5__ ui_gameType ; 
 TYPE_4__ ui_netGameType ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

void _UI_Init( qboolean inGameLoad ) {
	const char *menuSet;
	int start;

	//uiInfo.inGameLoad = inGameLoad;

	UI_RegisterCvars();
	UI_InitMemory();

	// cache redundant calulations
	trap_GetGlconfig( &uiInfo.uiDC.glconfig );

	// for 640x480 virtualized screen
	uiInfo.uiDC.yscale = uiInfo.uiDC.glconfig.vidHeight * (1.0/480.0);
	uiInfo.uiDC.xscale = uiInfo.uiDC.glconfig.vidWidth * (1.0/640.0);
	if ( uiInfo.uiDC.glconfig.vidWidth * 480 > uiInfo.uiDC.glconfig.vidHeight * 640 ) {
		// wide screen
		uiInfo.uiDC.bias = 0.5 * ( uiInfo.uiDC.glconfig.vidWidth - ( uiInfo.uiDC.glconfig.vidHeight * (640.0/480.0) ) );
	}
	else {
		// no wide screen
		uiInfo.uiDC.bias = 0;
	}


  //UI_Load();
	uiInfo.uiDC.registerShaderNoMip = &trap_R_RegisterShaderNoMip;
	uiInfo.uiDC.setColor = &UI_SetColor;
	uiInfo.uiDC.drawHandlePic = &UI_DrawHandlePic;
	uiInfo.uiDC.drawStretchPic = &trap_R_DrawStretchPic;
	uiInfo.uiDC.drawText = &Text_Paint;
	uiInfo.uiDC.textWidth = &Text_Width;
	uiInfo.uiDC.textHeight = &Text_Height;
	uiInfo.uiDC.registerModel = &trap_R_RegisterModel;
	uiInfo.uiDC.modelBounds = &trap_R_ModelBounds;
	uiInfo.uiDC.fillRect = &UI_FillRect;
	uiInfo.uiDC.drawRect = &_UI_DrawRect;
	uiInfo.uiDC.drawSides = &_UI_DrawSides;
	uiInfo.uiDC.drawTopBottom = &_UI_DrawTopBottom;
	uiInfo.uiDC.clearScene = &trap_R_ClearScene;
	uiInfo.uiDC.drawSides = &_UI_DrawSides;
	uiInfo.uiDC.addRefEntityToScene = &trap_R_AddRefEntityToScene;
	uiInfo.uiDC.renderScene = &trap_R_RenderScene;
	uiInfo.uiDC.registerFont = &trap_R_RegisterFont;
	uiInfo.uiDC.ownerDrawItem = &UI_OwnerDraw;
	uiInfo.uiDC.getValue = &UI_GetValue;
	uiInfo.uiDC.ownerDrawVisible = &UI_OwnerDrawVisible;
	uiInfo.uiDC.runScript = &UI_RunMenuScript;
	uiInfo.uiDC.getTeamColor = &UI_GetTeamColor;
	uiInfo.uiDC.setCVar = trap_Cvar_Set;
	uiInfo.uiDC.getCVarString = trap_Cvar_VariableStringBuffer;
	uiInfo.uiDC.getCVarValue = trap_Cvar_VariableValue;
	uiInfo.uiDC.drawTextWithCursor = &Text_PaintWithCursor;
	uiInfo.uiDC.setOverstrikeMode = &trap_Key_SetOverstrikeMode;
	uiInfo.uiDC.getOverstrikeMode = &trap_Key_GetOverstrikeMode;
	uiInfo.uiDC.startLocalSound = &trap_S_StartLocalSound;
	uiInfo.uiDC.ownerDrawHandleKey = &UI_OwnerDrawHandleKey;
	uiInfo.uiDC.feederCount = &UI_FeederCount;
	uiInfo.uiDC.feederItemImage = &UI_FeederItemImage;
	uiInfo.uiDC.feederItemText = &UI_FeederItemText;
	uiInfo.uiDC.feederSelection = &UI_FeederSelection;
	uiInfo.uiDC.setBinding = &trap_Key_SetBinding;
	uiInfo.uiDC.getBindingBuf = &trap_Key_GetBindingBuf;
	uiInfo.uiDC.keynumToStringBuf = &trap_Key_KeynumToStringBuf;
	uiInfo.uiDC.executeText = &trap_Cmd_ExecuteText;
	uiInfo.uiDC.Error = &Com_Error; 
	uiInfo.uiDC.Print = &Com_Printf; 
	uiInfo.uiDC.Pause = &UI_Pause;
	uiInfo.uiDC.ownerDrawWidth = &UI_OwnerDrawWidth;
	uiInfo.uiDC.registerSound = &trap_S_RegisterSound;
	uiInfo.uiDC.startBackgroundTrack = &trap_S_StartBackgroundTrack;
	uiInfo.uiDC.stopBackgroundTrack = &trap_S_StopBackgroundTrack;
	uiInfo.uiDC.playCinematic = &UI_PlayCinematic;
	uiInfo.uiDC.stopCinematic = &UI_StopCinematic;
	uiInfo.uiDC.drawCinematic = &UI_DrawCinematic;
	uiInfo.uiDC.runCinematicFrame = &UI_RunCinematicFrame;

	Init_Display(&uiInfo.uiDC);

	String_Init();
  
	uiInfo.uiDC.cursor	= trap_R_RegisterShaderNoMip( "menu/art/3_cursor2" );
	uiInfo.uiDC.whiteShader = trap_R_RegisterShaderNoMip( "white" );

	AssetCache();

	start = trap_Milliseconds();

  uiInfo.teamCount = 0;
  uiInfo.characterCount = 0;
  uiInfo.aliasCount = 0;

#ifdef PRE_RELEASE_TADEMO
	UI_ParseTeamInfo("demoteaminfo.txt");
	UI_ParseGameInfo("demogameinfo.txt");
#else
	UI_ParseTeamInfo("teaminfo.txt");
	UI_LoadTeams();
	UI_ParseGameInfo("gameinfo.txt");
#endif

	menuSet = UI_Cvar_VariableString("ui_menuFiles");
	if (menuSet == NULL || menuSet[0] == '\0') {
		menuSet = "ui/menus.txt";
	}

#if 0
	if (uiInfo.inGameLoad) {
		UI_LoadMenus("ui/ingame.txt", qtrue);
	} else { // bk010222: left this: UI_LoadMenus(menuSet, qtrue);
	}
#else 
	UI_LoadMenus(menuSet, qtrue);
	UI_LoadMenus("ui/ingame.txt", qfalse);
#endif
	
	Menus_CloseAll();

	trap_LAN_LoadCachedServers();
	UI_LoadBestScores(uiInfo.mapList[ui_currentMap.integer].mapLoadName, uiInfo.gameTypes[ui_gameType.integer].gtEnum);

	UI_BuildQ3Model_List();
	UI_LoadBots();

	// sets defaults for ui temp cvars
	uiInfo.effectsColor = gamecodetoui[(int)trap_Cvar_VariableValue("color1")-1];
	uiInfo.currentCrosshair = (int)trap_Cvar_VariableValue("cg_drawCrosshair");
	trap_Cvar_Set("ui_mousePitch", (trap_Cvar_VariableValue("m_pitch") >= 0) ? "0" : "1");

	uiInfo.serverStatus.currentServerCinematic = -1;
	uiInfo.previewMovie = -1;

	if (trap_Cvar_VariableValue("ui_TeamArenaFirstRun") == 0) {
		trap_Cvar_Set("s_volume", "0.8");
		trap_Cvar_Set("s_musicvolume", "0.5");
		trap_Cvar_Set("ui_TeamArenaFirstRun", "1");
	}

	trap_Cvar_Register(NULL, "debug_protocol", "", 0 );

	trap_Cvar_Set("ui_actualNetGameType", va("%d", ui_netGameType.integer));
}