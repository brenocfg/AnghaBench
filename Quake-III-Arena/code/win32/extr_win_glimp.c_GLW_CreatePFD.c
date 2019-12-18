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
typedef  scalar_t__ qboolean ;
struct TYPE_7__ {int /*<<< orphan*/  stereoEnabled; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_4; int member_18; int member_19; int cColorBits; int cDepthBits; int cStencilBits; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  member_25; int /*<<< orphan*/  member_24; int /*<<< orphan*/  member_23; int /*<<< orphan*/  member_22; int /*<<< orphan*/  member_21; int /*<<< orphan*/  member_20; int /*<<< orphan*/  member_17; int /*<<< orphan*/  member_16; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ PIXELFORMATDESCRIPTOR ;

/* Variables and functions */
 int PFD_DOUBLEBUFFER ; 
 int PFD_DRAW_TO_WINDOW ; 
 int /*<<< orphan*/  PFD_MAIN_PLANE ; 
 int /*<<< orphan*/  PFD_STEREO ; 
 int PFD_SUPPORT_OPENGL ; 
 int /*<<< orphan*/  PFD_TYPE_RGBA ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 TYPE_3__ glConfig ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void GLW_CreatePFD( PIXELFORMATDESCRIPTOR *pPFD, int colorbits, int depthbits, int stencilbits, qboolean stereo )
{
    PIXELFORMATDESCRIPTOR src = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
		1,								// version number
		PFD_DRAW_TO_WINDOW |			// support window
		PFD_SUPPORT_OPENGL |			// support OpenGL
		PFD_DOUBLEBUFFER,				// double buffered
		PFD_TYPE_RGBA,					// RGBA type
		24,								// 24-bit color depth
		0, 0, 0, 0, 0, 0,				// color bits ignored
		0,								// no alpha buffer
		0,								// shift bit ignored
		0,								// no accumulation buffer
		0, 0, 0, 0, 					// accum bits ignored
		24,								// 24-bit z-buffer	
		8,								// 8-bit stencil buffer
		0,								// no auxiliary buffer
		PFD_MAIN_PLANE,					// main layer
		0,								// reserved
		0, 0, 0							// layer masks ignored
    };

	src.cColorBits = colorbits;
	src.cDepthBits = depthbits;
	src.cStencilBits = stencilbits;

	if ( stereo )
	{
		ri.Printf( PRINT_ALL, "...attempting to use stereo\n" );
		src.dwFlags |= PFD_STEREO;
		glConfig.stereoEnabled = qtrue;
	}
	else
	{
		glConfig.stereoEnabled = qfalse;
	}

	*pPFD = src;
}