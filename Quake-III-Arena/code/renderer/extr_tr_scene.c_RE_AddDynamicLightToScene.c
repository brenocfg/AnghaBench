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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {float radius; float* color; int additive; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ dlight_t ;
struct TYPE_8__ {TYPE_1__* dlights; } ;
struct TYPE_7__ {scalar_t__ hardwareType; } ;
struct TYPE_6__ {size_t smpFrame; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 scalar_t__ GLHW_PERMEDIA2 ; 
 scalar_t__ GLHW_RIVA128 ; 
 scalar_t__ MAX_DLIGHTS ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 TYPE_4__** backEndData ; 
 TYPE_3__ glConfig ; 
 scalar_t__ r_numdlights ; 
 TYPE_2__ tr ; 

void RE_AddDynamicLightToScene( const vec3_t org, float intensity, float r, float g, float b, int additive ) {
	dlight_t	*dl;

	if ( !tr.registered ) {
		return;
	}
	if ( r_numdlights >= MAX_DLIGHTS ) {
		return;
	}
	if ( intensity <= 0 ) {
		return;
	}
	// these cards don't have the correct blend mode
	if ( glConfig.hardwareType == GLHW_RIVA128 || glConfig.hardwareType == GLHW_PERMEDIA2 ) {
		return;
	}
	dl = &backEndData[tr.smpFrame]->dlights[r_numdlights++];
	VectorCopy (org, dl->origin);
	dl->radius = intensity;
	dl->color[0] = r;
	dl->color[1] = g;
	dl->color[2] = b;
	dl->additive = additive;
}