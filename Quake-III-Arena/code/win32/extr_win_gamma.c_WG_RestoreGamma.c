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
struct TYPE_4__ {scalar_t__ deviceSupportsGamma; } ;
struct TYPE_3__ {int /*<<< orphan*/  hDC; } ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDeviceGammaRamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ glConfig ; 
 TYPE_1__ glw_state ; 
 int /*<<< orphan*/  qwglSetDeviceGammaRamp3DFX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_oldHardwareGamma ; 

void WG_RestoreGamma( void )
{
	if ( glConfig.deviceSupportsGamma )
	{
		if ( qwglSetDeviceGammaRamp3DFX )
		{
			qwglSetDeviceGammaRamp3DFX( glw_state.hDC, s_oldHardwareGamma );
		}
		else
		{
			HDC hDC;
			
			hDC = GetDC( GetDesktopWindow() );
			SetDeviceGammaRamp( hDC, s_oldHardwareGamma );
			ReleaseDC( GetDesktopWindow(), hDC );
		}
	}
}