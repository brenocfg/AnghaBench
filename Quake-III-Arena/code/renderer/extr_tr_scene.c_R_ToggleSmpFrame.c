#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ used; } ;
struct TYPE_8__ {TYPE_1__ commands; } ;
struct TYPE_7__ {scalar_t__ integer; } ;
struct TYPE_6__ {int smpFrame; } ;

/* Variables and functions */
 TYPE_4__** backEndData ; 
 scalar_t__ r_firstSceneDlight ; 
 scalar_t__ r_firstSceneDrawSurf ; 
 scalar_t__ r_firstSceneEntity ; 
 scalar_t__ r_firstScenePoly ; 
 scalar_t__ r_numdlights ; 
 scalar_t__ r_numentities ; 
 scalar_t__ r_numpolys ; 
 scalar_t__ r_numpolyverts ; 
 TYPE_3__* r_smp ; 
 TYPE_2__ tr ; 

void R_ToggleSmpFrame( void ) {
	if ( r_smp->integer ) {
		// use the other buffers next frame, because another CPU
		// may still be rendering into the current ones
		tr.smpFrame ^= 1;
	} else {
		tr.smpFrame = 0;
	}

	backEndData[tr.smpFrame]->commands.used = 0;

	r_firstSceneDrawSurf = 0;

	r_numdlights = 0;
	r_firstSceneDlight = 0;

	r_numentities = 0;
	r_firstSceneEntity = 0;

	r_numpolys = 0;
	r_firstScenePoly = 0;

	r_numpolyverts = 0;
}