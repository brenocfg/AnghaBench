#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vinfo ;
typedef  void* qboolean ;
struct TYPE_7__ {void* allowdisplaydepthchange; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_5__ {int dwOSVersionInfoSize; int dwMajorVersion; scalar_t__ dwPlatformId; int /*<<< orphan*/  dwBuildNumber; } ;
typedef  TYPE_1__ OSVERSIONINFO ;

/* Variables and functions */
 scalar_t__ GetVersionEx (TYPE_1__*) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ OSR2_BUILD_NUMBER ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 scalar_t__ VER_PLATFORM_WIN32_NT ; 
 scalar_t__ VER_PLATFORM_WIN32_WINDOWS ; 
 TYPE_3__ glw_state ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_2__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static qboolean GLW_CheckOSVersion( void )
{
#define OSR2_BUILD_NUMBER 1111

	OSVERSIONINFO	vinfo;

	vinfo.dwOSVersionInfoSize = sizeof(vinfo);

	glw_state.allowdisplaydepthchange = qfalse;

	if ( GetVersionEx( &vinfo) )
	{
		if ( vinfo.dwMajorVersion > 4 )
		{
			glw_state.allowdisplaydepthchange = qtrue;
		}
		else if ( vinfo.dwMajorVersion == 4 )
		{
			if ( vinfo.dwPlatformId == VER_PLATFORM_WIN32_NT )
			{
				glw_state.allowdisplaydepthchange = qtrue;
			}
			else if ( vinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
			{
				if ( LOWORD( vinfo.dwBuildNumber ) >= OSR2_BUILD_NUMBER )
				{
					glw_state.allowdisplaydepthchange = qtrue;
				}
			}
		}
	}
	else
	{
		ri.Printf( PRINT_ALL, "GLW_CheckOSVersion() - GetVersionEx failed\n" );
		return qfalse;
	}

	return qtrue;
}