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
typedef  void* qboolean ;
struct TYPE_4__ {void* modified; int /*<<< orphan*/  string; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  (* Cvar_Set ) (char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_FATAL ; 
 scalar_t__ GLW_LoadOpenGL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENGL_DRIVER_NAME ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _3DFX_DRIVER_NAME ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_2__* r_glDriver ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub3 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub5 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void GLW_StartOpenGL( void )
{
	qboolean attemptedOpenGL32 = qfalse;
	qboolean attempted3Dfx = qfalse;

	//
	// load and initialize the specific OpenGL driver
	//
	if ( !GLW_LoadOpenGL( r_glDriver->string ) )
	{
		if ( !Q_stricmp( r_glDriver->string, OPENGL_DRIVER_NAME ) )
		{
			attemptedOpenGL32 = qtrue;
		}
		else if ( !Q_stricmp( r_glDriver->string, _3DFX_DRIVER_NAME ) )
		{
			attempted3Dfx = qtrue;
		}

		if ( !attempted3Dfx )
		{
			attempted3Dfx = qtrue;
			if ( GLW_LoadOpenGL( _3DFX_DRIVER_NAME ) )
			{
				ri.Cvar_Set( "r_glDriver", _3DFX_DRIVER_NAME );
				r_glDriver->modified = qfalse;
			}
			else
			{
				if ( !attemptedOpenGL32 )
				{
					if ( !GLW_LoadOpenGL( OPENGL_DRIVER_NAME ) )
					{
						ri.Error( ERR_FATAL, "GLW_StartOpenGL() - could not load OpenGL subsystem\n" );
					}
					ri.Cvar_Set( "r_glDriver", OPENGL_DRIVER_NAME );
					r_glDriver->modified = qfalse;
				}
				else
				{
					ri.Error( ERR_FATAL, "GLW_StartOpenGL() - could not load OpenGL subsystem\n" );
				}
			}
		}
		else if ( !attemptedOpenGL32 )
		{
			attemptedOpenGL32 = qtrue;
			if ( GLW_LoadOpenGL( OPENGL_DRIVER_NAME ) )
			{
				ri.Cvar_Set( "r_glDriver", OPENGL_DRIVER_NAME );
				r_glDriver->modified = qfalse;
			}
			else
			{
				ri.Error( ERR_FATAL, "GLW_StartOpenGL() - could not load OpenGL subsystem\n" );
			}
		}
	}
}