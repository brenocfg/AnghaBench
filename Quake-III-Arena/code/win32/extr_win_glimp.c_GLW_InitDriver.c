#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_20__ {int /*<<< orphan*/  hWnd; } ;
struct TYPE_19__ {int colorBits; int depthBits; int stencilBits; int /*<<< orphan*/  stereoEnabled; } ;
struct TYPE_18__ {int desktopBitsPixel; int /*<<< orphan*/ * hDC; int /*<<< orphan*/  pixelFormatSet; } ;
struct TYPE_17__ {int integer; } ;
struct TYPE_16__ {int integer; } ;
struct TYPE_15__ {int integer; } ;
struct TYPE_14__ {scalar_t__ integer; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_12__ {int dwFlags; scalar_t__ cStencilBits; scalar_t__ cDepthBits; scalar_t__ cColorBits; } ;
typedef  TYPE_1__ PIXELFORMATDESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  GLW_CreatePFD (TYPE_1__*,int,int,int,scalar_t__) ; 
 int GLW_MakeContext (TYPE_1__*) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int PFD_STEREO ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int TRY_PFD_FAIL_HARD ; 
 int TRY_PFD_SUCCESS ; 
 TYPE_9__ g_wv ; 
 TYPE_8__ glConfig ; 
 TYPE_7__ glw_state ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_6__* r_colorbits ; 
 TYPE_5__* r_depthbits ; 
 TYPE_4__* r_stencilbits ; 
 TYPE_3__* r_stereo ; 
 TYPE_2__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static qboolean GLW_InitDriver( const char *drivername, int colorbits )
{
	int		tpfd;
	int		depthbits, stencilbits;
	static PIXELFORMATDESCRIPTOR pfd;		// save between frames since 'tr' gets cleared

	ri.Printf( PRINT_ALL, "Initializing OpenGL driver\n" );

	//
	// get a DC for our window if we don't already have one allocated
	//
	if ( glw_state.hDC == NULL )
	{
		ri.Printf( PRINT_ALL, "...getting DC: " );

		if ( ( glw_state.hDC = GetDC( g_wv.hWnd ) ) == NULL )
		{
			ri.Printf( PRINT_ALL, "failed\n" );
			return qfalse;
		}
		ri.Printf( PRINT_ALL, "succeeded\n" );
	}

	if ( colorbits == 0 )
	{
		colorbits = glw_state.desktopBitsPixel;
	}

	//
	// implicitly assume Z-buffer depth == desktop color depth
	//
	if ( r_depthbits->integer == 0 ) {
		if ( colorbits > 16 ) {
			depthbits = 24;
		} else {
			depthbits = 16;
		}
	} else {
		depthbits = r_depthbits->integer;
	}

	//
	// do not allow stencil if Z-buffer depth likely won't contain it
	//
	stencilbits = r_stencilbits->integer;
	if ( depthbits < 24 )
	{
		stencilbits = 0;
	}

	//
	// make two attempts to set the PIXELFORMAT
	//

	//
	// first attempt: r_colorbits, depthbits, and r_stencilbits
	//
	if ( !glw_state.pixelFormatSet )
	{
		GLW_CreatePFD( &pfd, colorbits, depthbits, stencilbits, r_stereo->integer );
		if ( ( tpfd = GLW_MakeContext( &pfd ) ) != TRY_PFD_SUCCESS )
		{
			if ( tpfd == TRY_PFD_FAIL_HARD )
			{
				ri.Printf( PRINT_WARNING, "...failed hard\n" );
				return qfalse;
			}

			//
			// punt if we've already tried the desktop bit depth and no stencil bits
			//
			if ( ( r_colorbits->integer == glw_state.desktopBitsPixel ) &&
				 ( stencilbits == 0 ) )
			{
				ReleaseDC( g_wv.hWnd, glw_state.hDC );
				glw_state.hDC = NULL;

				ri.Printf( PRINT_ALL, "...failed to find an appropriate PIXELFORMAT\n" );

				return qfalse;
			}

			//
			// second attempt: desktop's color bits and no stencil
			//
			if ( colorbits > glw_state.desktopBitsPixel )
			{
				colorbits = glw_state.desktopBitsPixel;
			}
			GLW_CreatePFD( &pfd, colorbits, depthbits, 0, r_stereo->integer );
			if ( GLW_MakeContext( &pfd ) != TRY_PFD_SUCCESS )
			{
				if ( glw_state.hDC )
				{
					ReleaseDC( g_wv.hWnd, glw_state.hDC );
					glw_state.hDC = NULL;
				}

				ri.Printf( PRINT_ALL, "...failed to find an appropriate PIXELFORMAT\n" );

				return qfalse;
			}
		}

		/*
		** report if stereo is desired but unavailable
		*/
		if ( !( pfd.dwFlags & PFD_STEREO ) && ( r_stereo->integer != 0 ) ) 
		{
			ri.Printf( PRINT_ALL, "...failed to select stereo pixel format\n" );
			glConfig.stereoEnabled = qfalse;
		}
	}

	/*
	** store PFD specifics 
	*/
	glConfig.colorBits = ( int ) pfd.cColorBits;
	glConfig.depthBits = ( int ) pfd.cDepthBits;
	glConfig.stencilBits = ( int ) pfd.cStencilBits;

	return qtrue;
}