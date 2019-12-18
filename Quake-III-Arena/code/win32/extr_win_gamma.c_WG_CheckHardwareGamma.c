#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ driverType; void* deviceSupportsGamma; } ;
struct TYPE_5__ {int /*<<< orphan*/  integer; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 scalar_t__ GLDRV_STANDALONE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 void* GetDeviceGammaRamp (int /*<<< orphan*/ ,int**) ; 
 int HIBYTE (int) ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ glConfig ; 
 void* qfalse ; 
 void* qtrue ; 
 void* qwglGetDeviceGammaRamp3DFX (int /*<<< orphan*/ ,int**) ; 
 scalar_t__ qwglSetDeviceGammaRamp3DFX ; 
 TYPE_2__* r_ignorehwgamma ; 
 TYPE_1__ ri ; 
 int** s_oldHardwareGamma ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 

void WG_CheckHardwareGamma( void )
{
	HDC			hDC;

	glConfig.deviceSupportsGamma = qfalse;

	if ( qwglSetDeviceGammaRamp3DFX )
	{
		glConfig.deviceSupportsGamma = qtrue;

		hDC = GetDC( GetDesktopWindow() );
		glConfig.deviceSupportsGamma = qwglGetDeviceGammaRamp3DFX( hDC, s_oldHardwareGamma );
		ReleaseDC( GetDesktopWindow(), hDC );

		return;
	}

	// non-3Dfx standalone drivers don't support gamma changes, period
	if ( glConfig.driverType == GLDRV_STANDALONE )
	{
		return;
	}

	if ( !r_ignorehwgamma->integer )
	{
		hDC = GetDC( GetDesktopWindow() );
		glConfig.deviceSupportsGamma = GetDeviceGammaRamp( hDC, s_oldHardwareGamma );
		ReleaseDC( GetDesktopWindow(), hDC );

		if ( glConfig.deviceSupportsGamma )
		{
			//
			// do a sanity check on the gamma values
			//
			if ( ( HIBYTE( s_oldHardwareGamma[0][255] ) <= HIBYTE( s_oldHardwareGamma[0][0] ) ) ||
				 ( HIBYTE( s_oldHardwareGamma[1][255] ) <= HIBYTE( s_oldHardwareGamma[1][0] ) ) ||
				 ( HIBYTE( s_oldHardwareGamma[2][255] ) <= HIBYTE( s_oldHardwareGamma[2][0] ) ) )
			{
				glConfig.deviceSupportsGamma = qfalse;
				ri.Printf( PRINT_WARNING, "WARNING: device has broken gamma support, generated gamma.dat\n" );
			}

			//
			// make sure that we didn't have a prior crash in the game, and if so we need to
			// restore the gamma values to at least a linear value
			//
			if ( ( HIBYTE( s_oldHardwareGamma[0][181] ) == 255 ) )
			{
				int g;

				ri.Printf( PRINT_WARNING, "WARNING: suspicious gamma tables, using linear ramp for restoration\n" );

				for ( g = 0; g < 255; g++ )
				{
					s_oldHardwareGamma[0][g] = g << 8;
					s_oldHardwareGamma[1][g] = g << 8;
					s_oldHardwareGamma[2][g] = g << 8;
				}
			}
		}
	}
}