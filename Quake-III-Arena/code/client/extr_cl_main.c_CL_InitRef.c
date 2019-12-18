#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  CIN_RunCinematic; int /*<<< orphan*/  CIN_PlayCinematic; int /*<<< orphan*/  CIN_UploadCinematic; int /*<<< orphan*/  (* Cvar_Set ) (char*,char*) ;int /*<<< orphan*/  Cvar_Get; int /*<<< orphan*/  FS_FileExists; int /*<<< orphan*/  FS_FileIsInPAK; int /*<<< orphan*/  FS_ListFiles; int /*<<< orphan*/  FS_FreeFileList; int /*<<< orphan*/  FS_WriteFile; int /*<<< orphan*/  FS_FreeFile; int /*<<< orphan*/  FS_ReadFile; int /*<<< orphan*/  CM_DrawDebugSurface; int /*<<< orphan*/  Hunk_FreeTempMemory; int /*<<< orphan*/  Hunk_AllocateTempMemory; int /*<<< orphan*/  Hunk_Alloc; int /*<<< orphan*/  Hunk_AllocDebug; int /*<<< orphan*/  Free; int /*<<< orphan*/  Malloc; int /*<<< orphan*/  Milliseconds; int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  Printf; int /*<<< orphan*/  Cmd_ExecuteText; int /*<<< orphan*/  Cmd_Argv; int /*<<< orphan*/  Cmd_Argc; int /*<<< orphan*/  Cmd_RemoveCommand; int /*<<< orphan*/  Cmd_AddCommand; } ;
typedef  TYPE_1__ refimport_t ;
typedef  int /*<<< orphan*/  refexport_t ;

/* Variables and functions */
 int /*<<< orphan*/  CIN_PlayCinematic ; 
 int /*<<< orphan*/  CIN_RunCinematic ; 
 int /*<<< orphan*/  CIN_UploadCinematic ; 
 int /*<<< orphan*/  CL_RefMalloc ; 
 int /*<<< orphan*/  CL_RefPrintf ; 
 int /*<<< orphan*/  CL_ScaledMilliseconds ; 
 int /*<<< orphan*/  CM_DrawDebugSurface ; 
 int /*<<< orphan*/  Cbuf_ExecuteText ; 
 int /*<<< orphan*/  Cmd_AddCommand ; 
 int /*<<< orphan*/  Cmd_Argc ; 
 int /*<<< orphan*/  Cmd_Argv ; 
 int /*<<< orphan*/  Cmd_RemoveCommand ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Cvar_Get ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  FS_FileExists ; 
 int /*<<< orphan*/  FS_FileIsInPAK ; 
 int /*<<< orphan*/  FS_FreeFile ; 
 int /*<<< orphan*/  FS_FreeFileList ; 
 int /*<<< orphan*/  FS_ListFiles ; 
 int /*<<< orphan*/  FS_ReadFile ; 
 int /*<<< orphan*/  FS_WriteFile ; 
 int /*<<< orphan*/ * GetRefAPI (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Hunk_Alloc ; 
 int /*<<< orphan*/  Hunk_AllocDebug ; 
 int /*<<< orphan*/  Hunk_AllocateTempMemory ; 
 int /*<<< orphan*/  Hunk_FreeTempMemory ; 
 int /*<<< orphan*/  REF_API_VERSION ; 
 int /*<<< orphan*/  Z_Free ; 
 int /*<<< orphan*/  hA3Dg_ExportRenderGeom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  re ; 

void CL_InitRef( void ) {
	refimport_t	ri;
	refexport_t	*ret;

	Com_Printf( "----- Initializing Renderer ----\n" );

	ri.Cmd_AddCommand = Cmd_AddCommand;
	ri.Cmd_RemoveCommand = Cmd_RemoveCommand;
	ri.Cmd_Argc = Cmd_Argc;
	ri.Cmd_Argv = Cmd_Argv;
	ri.Cmd_ExecuteText = Cbuf_ExecuteText;
	ri.Printf = CL_RefPrintf;
	ri.Error = Com_Error;
	ri.Milliseconds = CL_ScaledMilliseconds;
	ri.Malloc = CL_RefMalloc;
	ri.Free = Z_Free;
#ifdef HUNK_DEBUG
	ri.Hunk_AllocDebug = Hunk_AllocDebug;
#else
	ri.Hunk_Alloc = Hunk_Alloc;
#endif
	ri.Hunk_AllocateTempMemory = Hunk_AllocateTempMemory;
	ri.Hunk_FreeTempMemory = Hunk_FreeTempMemory;
	ri.CM_DrawDebugSurface = CM_DrawDebugSurface;
	ri.FS_ReadFile = FS_ReadFile;
	ri.FS_FreeFile = FS_FreeFile;
	ri.FS_WriteFile = FS_WriteFile;
	ri.FS_FreeFileList = FS_FreeFileList;
	ri.FS_ListFiles = FS_ListFiles;
	ri.FS_FileIsInPAK = FS_FileIsInPAK;
	ri.FS_FileExists = FS_FileExists;
	ri.Cvar_Get = Cvar_Get;
	ri.Cvar_Set = Cvar_Set;

	// cinematic stuff

	ri.CIN_UploadCinematic = CIN_UploadCinematic;
	ri.CIN_PlayCinematic = CIN_PlayCinematic;
	ri.CIN_RunCinematic = CIN_RunCinematic;

	ret = GetRefAPI( REF_API_VERSION, &ri );

#if defined __USEA3D && defined __A3D_GEOM
	hA3Dg_ExportRenderGeom (ret);
#endif

	Com_Printf( "-------------------------------\n");

	if ( !ret ) {
		Com_Error (ERR_FATAL, "Couldn't initialize refresh" );
	}

	re = *ret;

	// unpause so the cgame definately gets a snapshot and renders a frame
	Cvar_Set( "cl_paused", "0" );
}