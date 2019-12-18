#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ cvar_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_18__ {int /*<<< orphan*/  (* Cvar_Set ) (char*,char*) ;TYPE_1__* (* Cvar_Get ) (char*,char*,int) ;int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  hInstance; } ;
struct TYPE_15__ {char* vendor_string; char* renderer_string; char* version_string; char* extensions_string; int /*<<< orphan*/  hardwareType; } ;
struct TYPE_14__ {int /*<<< orphan*/  wndproc; } ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_LATCH ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  GLHW_3DFX_2D3D ; 
 int /*<<< orphan*/  GLHW_GENERIC ; 
 int /*<<< orphan*/  GLHW_PERMEDIA2 ; 
 int /*<<< orphan*/  GLHW_RAGEPRO ; 
 int /*<<< orphan*/  GLHW_RIVA128 ; 
 int /*<<< orphan*/  GLW_CheckOSVersion () ; 
 int /*<<< orphan*/  GLW_InitExtensions () ; 
 int /*<<< orphan*/  GLW_StartOpenGL () ; 
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_RENDERER ; 
 int /*<<< orphan*/  GL_VENDOR ; 
 int /*<<< orphan*/  GL_VERSION ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 scalar_t__ Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Q_strlwr (char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int /*<<< orphan*/  WG_CheckHardwareGamma () ; 
 TYPE_13__ g_wv ; 
 TYPE_12__ glConfig ; 
 TYPE_11__ glw_state ; 
 char* qglGetString (int /*<<< orphan*/ ) ; 
 TYPE_1__* r_allowSoftwareGL ; 
 TYPE_1__* r_maskMinidriver ; 
 TYPE_8__ ri ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ strstr (char*,char*) ; 
 TYPE_1__* stub1 (char*,char*,int) ; 
 TYPE_1__* stub10 (char*,char*,int) ; 
 int /*<<< orphan*/  stub11 (char*,char*) ; 
 int /*<<< orphan*/  stub12 (char*,char*) ; 
 int /*<<< orphan*/  stub13 (char*,char*) ; 
 int /*<<< orphan*/  stub14 (char*,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* stub4 (char*,char*,int) ; 
 TYPE_1__* stub5 (char*,char*,int) ; 
 TYPE_1__* stub6 (char*,char*,int) ; 
 TYPE_1__* stub7 (char*,char*,int) ; 
 int /*<<< orphan*/  stub8 (char*,char*) ; 
 int /*<<< orphan*/  stub9 (char*,char*) ; 

void GLimp_Init( void )
{
	char	buf[1024];
	cvar_t *lastValidRenderer = ri.Cvar_Get( "r_lastValidRenderer", "(uninitialized)", CVAR_ARCHIVE );
	cvar_t	*cv;

	ri.Printf( PRINT_ALL, "Initializing OpenGL subsystem\n" );

	//
	// check OS version to see if we can do fullscreen display changes
	//
	if ( !GLW_CheckOSVersion() )
	{
		ri.Error( ERR_FATAL, "GLimp_Init() - incorrect operating system\n" );
	}

	// save off hInstance and wndproc
	cv = ri.Cvar_Get( "win_hinstance", "", 0 );
	sscanf( cv->string, "%i", (int *)&g_wv.hInstance );

	cv = ri.Cvar_Get( "win_wndproc", "", 0 );
	sscanf( cv->string, "%i", (int *)&glw_state.wndproc );

	r_allowSoftwareGL = ri.Cvar_Get( "r_allowSoftwareGL", "0", CVAR_LATCH );
	r_maskMinidriver = ri.Cvar_Get( "r_maskMinidriver", "0", CVAR_LATCH );

	// load appropriate DLL and initialize subsystem
	GLW_StartOpenGL();

	// get our config strings
	Q_strncpyz( glConfig.vendor_string, qglGetString (GL_VENDOR), sizeof( glConfig.vendor_string ) );
	Q_strncpyz( glConfig.renderer_string, qglGetString (GL_RENDERER), sizeof( glConfig.renderer_string ) );
	Q_strncpyz( glConfig.version_string, qglGetString (GL_VERSION), sizeof( glConfig.version_string ) );
	Q_strncpyz( glConfig.extensions_string, qglGetString (GL_EXTENSIONS), sizeof( glConfig.extensions_string ) );

	//
	// chipset specific configuration
	//
	Q_strncpyz( buf, glConfig.renderer_string, sizeof(buf) );
	Q_strlwr( buf );

	//
	// NOTE: if changing cvars, do it within this block.  This allows them
	// to be overridden when testing driver fixes, etc. but only sets
	// them to their default state when the hardware is first installed/run.
	//
	if ( Q_stricmp( lastValidRenderer->string, glConfig.renderer_string ) )
	{
		glConfig.hardwareType = GLHW_GENERIC;

		ri.Cvar_Set( "r_textureMode", "GL_LINEAR_MIPMAP_NEAREST" );

		// VOODOO GRAPHICS w/ 2MB
		if ( strstr( buf, "voodoo graphics/1 tmu/2 mb" ) )
		{
			ri.Cvar_Set( "r_picmip", "2" );
			ri.Cvar_Get( "r_picmip", "1", CVAR_ARCHIVE | CVAR_LATCH );
		}
		else
		{
			ri.Cvar_Set( "r_picmip", "1" );

			if ( strstr( buf, "rage 128" ) || strstr( buf, "rage128" ) )
			{
				ri.Cvar_Set( "r_finish", "0" );
			}
			// Savage3D and Savage4 should always have trilinear enabled
			else if ( strstr( buf, "savage3d" ) || strstr( buf, "s3 savage4" ) )
			{
				ri.Cvar_Set( "r_texturemode", "GL_LINEAR_MIPMAP_LINEAR" );
			}
		}
	}
	
	//
	// this is where hardware specific workarounds that should be
	// detected/initialized every startup should go.
	//
	if ( strstr( buf, "banshee" ) || strstr( buf, "voodoo3" ) )
	{
		glConfig.hardwareType = GLHW_3DFX_2D3D;
	}
	// VOODOO GRAPHICS w/ 2MB
	else if ( strstr( buf, "voodoo graphics/1 tmu/2 mb" ) )
	{
	}
	else if ( strstr( buf, "glzicd" ) )
	{
	}
	else if ( strstr( buf, "rage pro" ) || strstr( buf, "Rage Pro" ) || strstr( buf, "ragepro" ) )
	{
		glConfig.hardwareType = GLHW_RAGEPRO;
	}
	else if ( strstr( buf, "rage 128" ) )
	{
	}
	else if ( strstr( buf, "permedia2" ) )
	{
		glConfig.hardwareType = GLHW_PERMEDIA2;
	}
	else if ( strstr( buf, "riva 128" ) )
	{
		glConfig.hardwareType = GLHW_RIVA128;
	}
	else if ( strstr( buf, "riva tnt " ) )
	{
	}

	ri.Cvar_Set( "r_lastValidRenderer", glConfig.renderer_string );

	GLW_InitExtensions();
	WG_CheckHardwareGamma();
}