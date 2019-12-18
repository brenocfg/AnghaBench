#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* PC_AddGlobalDefine ) (int) ;int (* PC_LoadSourceHandle ) (int) ;int (* PC_FreeSourceHandle ) (int) ;int (* PC_ReadTokenHandle ) (int,int) ;int (* PC_SourceFileAndLine ) (int,int,int) ;} ;
struct TYPE_3__ {int (* RegisterModel ) (int) ;int (* RegisterSkin ) (int) ;int (* RegisterShaderNoMip ) (int) ;int /*<<< orphan*/  (* RemapShader ) (int,int,int) ;int /*<<< orphan*/  (* RegisterFont ) (int,int,int) ;int /*<<< orphan*/  (* LerpTag ) (int,int,int,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* ModelBounds ) (int,int,int) ;int /*<<< orphan*/  (* DrawStretchPic ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* SetColor ) (int) ;int /*<<< orphan*/  (* RenderScene ) (int) ;int /*<<< orphan*/  (* AddLightToScene ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* AddPolyToScene ) (int,int,int,int) ;int /*<<< orphan*/  (* AddRefEntityToScene ) (int) ;int /*<<< orphan*/  (* ClearScene ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CIN_DrawCinematic (int) ; 
 int CIN_PlayCinematic (int,int,int,int,int,int) ; 
 int CIN_RunCinematic (int) ; 
 int /*<<< orphan*/  CIN_SetExtents (int,int,int,int,int) ; 
 int CIN_StopCinematic (int) ; 
 int /*<<< orphan*/  CLUI_GetCDKey (int,int) ; 
 int /*<<< orphan*/  CLUI_SetCDKey (int) ; 
 int CL_CDKeyValidate (int,int) ; 
 int /*<<< orphan*/  CL_GetGlconfig (int) ; 
 int /*<<< orphan*/  Cbuf_ExecuteText (int,int) ; 
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_ArgvBuffer (int,int,int) ; 
 int /*<<< orphan*/  Com_DPrintf (char*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  Com_Memcpy (int,int,int) ; 
 int /*<<< orphan*/  Com_Memset (int,int,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,int) ; 
 int Com_RealTime (int) ; 
 int /*<<< orphan*/  Cvar_Get (int,int,int) ; 
 int /*<<< orphan*/  Cvar_InfoStringBuffer (int,int,int) ; 
 int /*<<< orphan*/  Cvar_Register (int,int,int,int) ; 
 int /*<<< orphan*/  Cvar_Reset (int) ; 
 int /*<<< orphan*/  Cvar_Set (int,int) ; 
 int /*<<< orphan*/  Cvar_SetValue (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_Update (int) ; 
 int /*<<< orphan*/  Cvar_VariableStringBuffer (int,int,int) ; 
 int /*<<< orphan*/  Cvar_VariableValue (int) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  FS_FCloseFile (int) ; 
 int FS_FOpenFileByMode (int,int,int) ; 
 int FS_GetFileList (int,int,int,int) ; 
 int /*<<< orphan*/  FS_Read2 (int,int,int) ; 
 int FS_Seek (int,int,int) ; 
 int /*<<< orphan*/  FS_Write (int,int,int) ; 
 int FloatAsInt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientState (int) ; 
 int /*<<< orphan*/  GetClipboardData (int,int) ; 
 int GetConfigString (int,int,int) ; 
 int Hunk_MemoryRemaining () ; 
 int /*<<< orphan*/  Key_ClearStates () ; 
 int /*<<< orphan*/  Key_GetBindingBuf (int,int,int) ; 
 int Key_GetCatcher () ; 
 int Key_GetOverstrikeMode () ; 
 int Key_IsDown (int) ; 
 int /*<<< orphan*/  Key_KeynumToStringBuf (int,int,int) ; 
 int /*<<< orphan*/  Key_SetBinding (int,int) ; 
 int /*<<< orphan*/  Key_SetCatcher (int) ; 
 int /*<<< orphan*/  Key_SetOverstrikeMode (int) ; 
 int LAN_AddServer (int,int,int) ; 
 int /*<<< orphan*/  LAN_ClearPing (int) ; 
 int LAN_CompareServers (int,int,int,int,int) ; 
 int /*<<< orphan*/  LAN_GetPing (int,int,int,int) ; 
 int /*<<< orphan*/  LAN_GetPingInfo (int,int,int) ; 
 int LAN_GetPingQueueCount () ; 
 int /*<<< orphan*/  LAN_GetServerAddressString (int,int,int,int) ; 
 int LAN_GetServerCount (int) ; 
 int /*<<< orphan*/  LAN_GetServerInfo (int,int,int,int) ; 
 int LAN_GetServerPing (int,int) ; 
 int LAN_GetServerStatus (int,int,int) ; 
 int /*<<< orphan*/  LAN_LoadCachedServers () ; 
 int /*<<< orphan*/  LAN_MarkServerVisible (int,int,int) ; 
 int /*<<< orphan*/  LAN_RemoveServer (int,int) ; 
 int /*<<< orphan*/  LAN_ResetPings (int) ; 
 int /*<<< orphan*/  LAN_SaveServersToCache () ; 
 int LAN_ServerIsVisible (int,int) ; 
 int LAN_UpdateVisiblePings (int) ; 
 int /*<<< orphan*/  SCR_UpdateScreen () ; 
 int S_RegisterSound (int,int) ; 
 int /*<<< orphan*/  S_StartBackgroundTrack (int,int) ; 
 int /*<<< orphan*/  S_StartLocalSound (int,int) ; 
 int /*<<< orphan*/  S_StopBackgroundTrack () ; 
 int Sys_Milliseconds () ; 
#define  UI_ARGC 223 
#define  UI_ARGV 222 
#define  UI_ATAN2 221 
#define  UI_CEIL 220 
#define  UI_CIN_DRAWCINEMATIC 219 
#define  UI_CIN_PLAYCINEMATIC 218 
#define  UI_CIN_RUNCINEMATIC 217 
#define  UI_CIN_SETEXTENTS 216 
#define  UI_CIN_STOPCINEMATIC 215 
#define  UI_CMD_EXECUTETEXT 214 
#define  UI_CM_LERPTAG 213 
#define  UI_COS 212 
#define  UI_CVAR_CREATE 211 
#define  UI_CVAR_INFOSTRINGBUFFER 210 
#define  UI_CVAR_REGISTER 209 
#define  UI_CVAR_RESET 208 
#define  UI_CVAR_SET 207 
#define  UI_CVAR_SETVALUE 206 
#define  UI_CVAR_UPDATE 205 
#define  UI_CVAR_VARIABLESTRINGBUFFER 204 
#define  UI_CVAR_VARIABLEVALUE 203 
#define  UI_ERROR 202 
#define  UI_FLOOR 201 
#define  UI_FS_FCLOSEFILE 200 
#define  UI_FS_FOPENFILE 199 
#define  UI_FS_GETFILELIST 198 
#define  UI_FS_READ 197 
#define  UI_FS_SEEK 196 
#define  UI_FS_WRITE 195 
#define  UI_GETCLIENTSTATE 194 
#define  UI_GETCLIPBOARDDATA 193 
#define  UI_GETCONFIGSTRING 192 
#define  UI_GETGLCONFIG 191 
#define  UI_GET_CDKEY 190 
#define  UI_KEY_CLEARSTATES 189 
#define  UI_KEY_GETBINDINGBUF 188 
#define  UI_KEY_GETCATCHER 187 
#define  UI_KEY_GETOVERSTRIKEMODE 186 
#define  UI_KEY_ISDOWN 185 
#define  UI_KEY_KEYNUMTOSTRINGBUF 184 
#define  UI_KEY_SETBINDING 183 
#define  UI_KEY_SETCATCHER 182 
#define  UI_KEY_SETOVERSTRIKEMODE 181 
#define  UI_LAN_ADDSERVER 180 
#define  UI_LAN_CLEARPING 179 
#define  UI_LAN_COMPARESERVERS 178 
#define  UI_LAN_GETPING 177 
#define  UI_LAN_GETPINGINFO 176 
#define  UI_LAN_GETPINGQUEUECOUNT 175 
#define  UI_LAN_GETSERVERADDRESSSTRING 174 
#define  UI_LAN_GETSERVERCOUNT 173 
#define  UI_LAN_GETSERVERINFO 172 
#define  UI_LAN_GETSERVERPING 171 
#define  UI_LAN_LOADCACHEDSERVERS 170 
#define  UI_LAN_MARKSERVERVISIBLE 169 
#define  UI_LAN_REMOVESERVER 168 
#define  UI_LAN_RESETPINGS 167 
#define  UI_LAN_SAVECACHEDSERVERS 166 
#define  UI_LAN_SERVERISVISIBLE 165 
#define  UI_LAN_SERVERSTATUS 164 
#define  UI_LAN_UPDATEVISIBLEPINGS 163 
#define  UI_MEMCPY 162 
#define  UI_MEMORY_REMAINING 161 
#define  UI_MEMSET 160 
#define  UI_MILLISECONDS 159 
#define  UI_PC_ADD_GLOBAL_DEFINE 158 
#define  UI_PC_FREE_SOURCE 157 
#define  UI_PC_LOAD_SOURCE 156 
#define  UI_PC_READ_TOKEN 155 
#define  UI_PC_SOURCE_FILE_AND_LINE 154 
#define  UI_PRINT 153 
#define  UI_REAL_TIME 152 
#define  UI_R_ADDLIGHTTOSCENE 151 
#define  UI_R_ADDPOLYTOSCENE 150 
#define  UI_R_ADDREFENTITYTOSCENE 149 
#define  UI_R_CLEARSCENE 148 
#define  UI_R_DRAWSTRETCHPIC 147 
#define  UI_R_MODELBOUNDS 146 
#define  UI_R_REGISTERFONT 145 
#define  UI_R_REGISTERMODEL 144 
#define  UI_R_REGISTERSHADERNOMIP 143 
#define  UI_R_REGISTERSKIN 142 
#define  UI_R_REMAP_SHADER 141 
#define  UI_R_RENDERSCENE 140 
#define  UI_R_SETCOLOR 139 
#define  UI_SET_CDKEY 138 
#define  UI_SET_PBCLSTATUS 137 
#define  UI_SIN 136 
#define  UI_SQRT 135 
#define  UI_STRNCPY 134 
#define  UI_S_REGISTERSOUND 133 
#define  UI_S_STARTBACKGROUNDTRACK 132 
#define  UI_S_STARTLOCALSOUND 131 
#define  UI_S_STOPBACKGROUNDTRACK 130 
#define  UI_UPDATESCREEN 129 
#define  UI_VERIFY_CDKEY 128 
 int VMA (int) ; 
 int /*<<< orphan*/  VMF (int) ; 
 int /*<<< orphan*/  atan2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* botlib_export ; 
 int /*<<< orphan*/  ceil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floor (int /*<<< orphan*/ ) ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  sin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqrt (int /*<<< orphan*/ ) ; 
 scalar_t__ strncpy (int,int,int) ; 
 int stub1 (int) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub11 (int,int,int) ; 
 int /*<<< orphan*/  stub12 (int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub13 (int,int,int) ; 
 int stub14 (int) ; 
 int stub15 (int) ; 
 int stub16 (int) ; 
 int stub17 (int,int) ; 
 int stub18 (int,int,int) ; 
 int /*<<< orphan*/  stub19 (int,int,int) ; 
 int stub2 (int) ; 
 int stub3 (int) ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  stub5 (int) ; 
 int /*<<< orphan*/  stub6 (int,int,int,int) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int) ; 
 int /*<<< orphan*/  stub9 (int) ; 

int CL_UISystemCalls( int *args ) {
	switch( args[0] ) {
	case UI_ERROR:
		Com_Error( ERR_DROP, "%s", VMA(1) );
		return 0;

	case UI_PRINT:
		Com_Printf( "%s", VMA(1) );
		return 0;

	case UI_MILLISECONDS:
		return Sys_Milliseconds();

	case UI_CVAR_REGISTER:
		Cvar_Register( VMA(1), VMA(2), VMA(3), args[4] ); 
		return 0;

	case UI_CVAR_UPDATE:
		Cvar_Update( VMA(1) );
		return 0;

	case UI_CVAR_SET:
		Cvar_Set( VMA(1), VMA(2) );
		return 0;

	case UI_CVAR_VARIABLEVALUE:
		return FloatAsInt( Cvar_VariableValue( VMA(1) ) );

	case UI_CVAR_VARIABLESTRINGBUFFER:
		Cvar_VariableStringBuffer( VMA(1), VMA(2), args[3] );
		return 0;

	case UI_CVAR_SETVALUE:
		Cvar_SetValue( VMA(1), VMF(2) );
		return 0;

	case UI_CVAR_RESET:
		Cvar_Reset( VMA(1) );
		return 0;

	case UI_CVAR_CREATE:
		Cvar_Get( VMA(1), VMA(2), args[3] );
		return 0;

	case UI_CVAR_INFOSTRINGBUFFER:
		Cvar_InfoStringBuffer( args[1], VMA(2), args[3] );
		return 0;

	case UI_ARGC:
		return Cmd_Argc();

	case UI_ARGV:
		Cmd_ArgvBuffer( args[1], VMA(2), args[3] );
		return 0;

	case UI_CMD_EXECUTETEXT:
		Cbuf_ExecuteText( args[1], VMA(2) );
		return 0;

	case UI_FS_FOPENFILE:
		return FS_FOpenFileByMode( VMA(1), VMA(2), args[3] );

	case UI_FS_READ:
		FS_Read2( VMA(1), args[2], args[3] );
		return 0;

	case UI_FS_WRITE:
		FS_Write( VMA(1), args[2], args[3] );
		return 0;

	case UI_FS_FCLOSEFILE:
		FS_FCloseFile( args[1] );
		return 0;

	case UI_FS_GETFILELIST:
		return FS_GetFileList( VMA(1), VMA(2), VMA(3), args[4] );

	case UI_FS_SEEK:
		return FS_Seek( args[1], args[2], args[3] );
	
	case UI_R_REGISTERMODEL:
		return re.RegisterModel( VMA(1) );

	case UI_R_REGISTERSKIN:
		return re.RegisterSkin( VMA(1) );

	case UI_R_REGISTERSHADERNOMIP:
		return re.RegisterShaderNoMip( VMA(1) );

	case UI_R_CLEARSCENE:
		re.ClearScene();
		return 0;

	case UI_R_ADDREFENTITYTOSCENE:
		re.AddRefEntityToScene( VMA(1) );
		return 0;

	case UI_R_ADDPOLYTOSCENE:
		re.AddPolyToScene( args[1], args[2], VMA(3), 1 );
		return 0;

	case UI_R_ADDLIGHTTOSCENE:
		re.AddLightToScene( VMA(1), VMF(2), VMF(3), VMF(4), VMF(5) );
		return 0;

	case UI_R_RENDERSCENE:
		re.RenderScene( VMA(1) );
		return 0;

	case UI_R_SETCOLOR:
		re.SetColor( VMA(1) );
		return 0;

	case UI_R_DRAWSTRETCHPIC:
		re.DrawStretchPic( VMF(1), VMF(2), VMF(3), VMF(4), VMF(5), VMF(6), VMF(7), VMF(8), args[9] );
		return 0;

  case UI_R_MODELBOUNDS:
		re.ModelBounds( args[1], VMA(2), VMA(3) );
		return 0;

	case UI_UPDATESCREEN:
		SCR_UpdateScreen();
		return 0;

	case UI_CM_LERPTAG:
		re.LerpTag( VMA(1), args[2], args[3], args[4], VMF(5), VMA(6) );
		return 0;

	case UI_S_REGISTERSOUND:
		return S_RegisterSound( VMA(1), args[2] );

	case UI_S_STARTLOCALSOUND:
		S_StartLocalSound( args[1], args[2] );
		return 0;

	case UI_KEY_KEYNUMTOSTRINGBUF:
		Key_KeynumToStringBuf( args[1], VMA(2), args[3] );
		return 0;

	case UI_KEY_GETBINDINGBUF:
		Key_GetBindingBuf( args[1], VMA(2), args[3] );
		return 0;

	case UI_KEY_SETBINDING:
		Key_SetBinding( args[1], VMA(2) );
		return 0;

	case UI_KEY_ISDOWN:
		return Key_IsDown( args[1] );

	case UI_KEY_GETOVERSTRIKEMODE:
		return Key_GetOverstrikeMode();

	case UI_KEY_SETOVERSTRIKEMODE:
		Key_SetOverstrikeMode( args[1] );
		return 0;

	case UI_KEY_CLEARSTATES:
		Key_ClearStates();
		return 0;

	case UI_KEY_GETCATCHER:
		return Key_GetCatcher();

	case UI_KEY_SETCATCHER:
		Key_SetCatcher( args[1] );
		return 0;

	case UI_GETCLIPBOARDDATA:
		GetClipboardData( VMA(1), args[2] );
		return 0;

	case UI_GETCLIENTSTATE:
		GetClientState( VMA(1) );
		return 0;		

	case UI_GETGLCONFIG:
		CL_GetGlconfig( VMA(1) );
		return 0;

	case UI_GETCONFIGSTRING:
		return GetConfigString( args[1], VMA(2), args[3] );

	case UI_LAN_LOADCACHEDSERVERS:
		LAN_LoadCachedServers();
		return 0;

	case UI_LAN_SAVECACHEDSERVERS:
		LAN_SaveServersToCache();
		return 0;

	case UI_LAN_ADDSERVER:
		return LAN_AddServer(args[1], VMA(2), VMA(3));

	case UI_LAN_REMOVESERVER:
		LAN_RemoveServer(args[1], VMA(2));
		return 0;

	case UI_LAN_GETPINGQUEUECOUNT:
		return LAN_GetPingQueueCount();

	case UI_LAN_CLEARPING:
		LAN_ClearPing( args[1] );
		return 0;

	case UI_LAN_GETPING:
		LAN_GetPing( args[1], VMA(2), args[3], VMA(4) );
		return 0;

	case UI_LAN_GETPINGINFO:
		LAN_GetPingInfo( args[1], VMA(2), args[3] );
		return 0;

	case UI_LAN_GETSERVERCOUNT:
		return LAN_GetServerCount(args[1]);

	case UI_LAN_GETSERVERADDRESSSTRING:
		LAN_GetServerAddressString( args[1], args[2], VMA(3), args[4] );
		return 0;

	case UI_LAN_GETSERVERINFO:
		LAN_GetServerInfo( args[1], args[2], VMA(3), args[4] );
		return 0;

	case UI_LAN_GETSERVERPING:
		return LAN_GetServerPing( args[1], args[2] );

	case UI_LAN_MARKSERVERVISIBLE:
		LAN_MarkServerVisible( args[1], args[2], args[3] );
		return 0;

	case UI_LAN_SERVERISVISIBLE:
		return LAN_ServerIsVisible( args[1], args[2] );

	case UI_LAN_UPDATEVISIBLEPINGS:
		return LAN_UpdateVisiblePings( args[1] );

	case UI_LAN_RESETPINGS:
		LAN_ResetPings( args[1] );
		return 0;

	case UI_LAN_SERVERSTATUS:
		return LAN_GetServerStatus( VMA(1), VMA(2), args[3] );

	case UI_LAN_COMPARESERVERS:
		return LAN_CompareServers( args[1], args[2], args[3], args[4], args[5] );

	case UI_MEMORY_REMAINING:
		return Hunk_MemoryRemaining();

	case UI_GET_CDKEY:
		CLUI_GetCDKey( VMA(1), args[2] );
		return 0;

	case UI_SET_CDKEY:
		CLUI_SetCDKey( VMA(1) );
		return 0;
	
	case UI_SET_PBCLSTATUS:
		return 0;	

	case UI_R_REGISTERFONT:
		re.RegisterFont( VMA(1), args[2], VMA(3));
		return 0;

	case UI_MEMSET:
		Com_Memset( VMA(1), args[2], args[3] );
		return 0;

	case UI_MEMCPY:
		Com_Memcpy( VMA(1), VMA(2), args[3] );
		return 0;

	case UI_STRNCPY:
		return (int)strncpy( VMA(1), VMA(2), args[3] );

	case UI_SIN:
		return FloatAsInt( sin( VMF(1) ) );

	case UI_COS:
		return FloatAsInt( cos( VMF(1) ) );

	case UI_ATAN2:
		return FloatAsInt( atan2( VMF(1), VMF(2) ) );

	case UI_SQRT:
		return FloatAsInt( sqrt( VMF(1) ) );

	case UI_FLOOR:
		return FloatAsInt( floor( VMF(1) ) );

	case UI_CEIL:
		return FloatAsInt( ceil( VMF(1) ) );

	case UI_PC_ADD_GLOBAL_DEFINE:
		return botlib_export->PC_AddGlobalDefine( VMA(1) );
	case UI_PC_LOAD_SOURCE:
		return botlib_export->PC_LoadSourceHandle( VMA(1) );
	case UI_PC_FREE_SOURCE:
		return botlib_export->PC_FreeSourceHandle( args[1] );
	case UI_PC_READ_TOKEN:
		return botlib_export->PC_ReadTokenHandle( args[1], VMA(2) );
	case UI_PC_SOURCE_FILE_AND_LINE:
		return botlib_export->PC_SourceFileAndLine( args[1], VMA(2), VMA(3) );

	case UI_S_STOPBACKGROUNDTRACK:
		S_StopBackgroundTrack();
		return 0;
	case UI_S_STARTBACKGROUNDTRACK:
		S_StartBackgroundTrack( VMA(1), VMA(2));
		return 0;

	case UI_REAL_TIME:
		return Com_RealTime( VMA(1) );

	case UI_CIN_PLAYCINEMATIC:
	  Com_DPrintf("UI_CIN_PlayCinematic\n");
	  return CIN_PlayCinematic(VMA(1), args[2], args[3], args[4], args[5], args[6]);

	case UI_CIN_STOPCINEMATIC:
	  return CIN_StopCinematic(args[1]);

	case UI_CIN_RUNCINEMATIC:
	  return CIN_RunCinematic(args[1]);

	case UI_CIN_DRAWCINEMATIC:
	  CIN_DrawCinematic(args[1]);
	  return 0;

	case UI_CIN_SETEXTENTS:
	  CIN_SetExtents(args[1], args[2], args[3], args[4], args[5]);
	  return 0;

	case UI_R_REMAP_SHADER:
		re.RemapShader( VMA(1), VMA(2), VMA(3) );
		return 0;

	case UI_VERIFY_CDKEY:
		return CL_CDKeyValidate(VMA(1), VMA(2));


		
	default:
		Com_Error( ERR_DROP, "Bad UI system trap: %i", args[0] );

	}

	return 0;
}