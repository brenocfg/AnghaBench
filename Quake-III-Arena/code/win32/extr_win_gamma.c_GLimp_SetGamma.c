#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vinfo ;
struct TYPE_9__ {int /*<<< orphan*/  deviceSupportsGamma; } ;
struct TYPE_8__ {int /*<<< orphan*/  hDC; } ;
struct TYPE_7__ {scalar_t__ integer; } ;
struct TYPE_6__ {int dwOSVersionInfoSize; int dwMajorVersion; scalar_t__ dwPlatformId; } ;
typedef  TYPE_1__ OSVERSIONINFO ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  GetVersionEx (TYPE_1__*) ; 
 int SetDeviceGammaRamp (int /*<<< orphan*/ ,unsigned short**) ; 
 scalar_t__ VER_PLATFORM_WIN32_NT ; 
 TYPE_4__ glConfig ; 
 TYPE_3__ glw_state ; 
 int /*<<< orphan*/  qwglSetDeviceGammaRamp3DFX (int /*<<< orphan*/ ,unsigned short**) ; 
 TYPE_2__* r_ignorehwgamma ; 

void GLimp_SetGamma( unsigned char red[256], unsigned char green[256], unsigned char blue[256] ) {
	unsigned short table[3][256];
	int		i, j;
	int		ret;
	OSVERSIONINFO	vinfo;

	if ( !glConfig.deviceSupportsGamma || r_ignorehwgamma->integer || !glw_state.hDC ) {
		return;
	}

//mapGammaMax();

	for ( i = 0; i < 256; i++ ) {
		table[0][i] = ( ( ( unsigned short ) red[i] ) << 8 ) | red[i];
		table[1][i] = ( ( ( unsigned short ) green[i] ) << 8 ) | green[i];
		table[2][i] = ( ( ( unsigned short ) blue[i] ) << 8 ) | blue[i];
	}

	// Win2K puts this odd restriction on gamma ramps...
	vinfo.dwOSVersionInfoSize = sizeof(vinfo);
	GetVersionEx( &vinfo );
	if ( vinfo.dwMajorVersion == 5 && vinfo.dwPlatformId == VER_PLATFORM_WIN32_NT ) {
		Com_DPrintf( "performing W2K gamma clamp.\n" );
		for ( j = 0 ; j < 3 ; j++ ) {
			for ( i = 0 ; i < 128 ; i++ ) {
				if ( table[j][i] > ( (128+i) << 8 ) ) {
					table[j][i] = (128+i) << 8;
				}
			}
			if ( table[j][127] > 254<<8 ) {
				table[j][127] = 254<<8;
			}
		}
	} else {
		Com_DPrintf( "skipping W2K gamma clamp.\n" );
	}

	// enforce constantly increasing
	for ( j = 0 ; j < 3 ; j++ ) {
		for ( i = 1 ; i < 256 ; i++ ) {
			if ( table[j][i] < table[j][i-1] ) {
				table[j][i] = table[j][i-1];
			}
		}
	}


	if ( qwglSetDeviceGammaRamp3DFX )
	{
		qwglSetDeviceGammaRamp3DFX( glw_state.hDC, table );
	}
	else
	{
		ret = SetDeviceGammaRamp( glw_state.hDC, table );
		if ( !ret ) {
			Com_Printf( "SetDeviceGammaRamp failed.\n" );
		}
	}
}