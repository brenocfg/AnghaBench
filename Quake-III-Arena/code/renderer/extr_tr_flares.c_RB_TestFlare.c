#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_12__ {float eyeZ; float fadeTime; float drawIntensity; void* visible; int /*<<< orphan*/  windowY; int /*<<< orphan*/  windowX; } ;
typedef  TYPE_4__ flare_t ;
struct TYPE_11__ {float time; } ;
struct TYPE_10__ {int* projectionMatrix; } ;
struct TYPE_9__ {int /*<<< orphan*/  c_flareTests; } ;
struct TYPE_15__ {TYPE_3__ refdef; TYPE_2__ viewParms; TYPE_1__ pc; } ;
struct TYPE_14__ {void* finishCalled; } ;
struct TYPE_13__ {float value; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DEPTH_COMPONENT ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 TYPE_7__ backEnd ; 
 TYPE_6__ glState ; 
 void* qfalse ; 
 int /*<<< orphan*/  qglReadPixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 void* qtrue ; 
 TYPE_5__* r_flareFade ; 

void RB_TestFlare( flare_t *f ) {
	float			depth;
	qboolean		visible;
	float			fade;
	float			screenZ;

	backEnd.pc.c_flareTests++;

	// doing a readpixels is as good as doing a glFinish(), so
	// don't bother with another sync
	glState.finishCalled = qfalse;

	// read back the z buffer contents
	qglReadPixels( f->windowX, f->windowY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth );

	screenZ = backEnd.viewParms.projectionMatrix[14] / 
		( ( 2*depth - 1 ) * backEnd.viewParms.projectionMatrix[11] - backEnd.viewParms.projectionMatrix[10] );

	visible = ( -f->eyeZ - -screenZ ) < 24;

	if ( visible ) {
		if ( !f->visible ) {
			f->visible = qtrue;
			f->fadeTime = backEnd.refdef.time - 1;
		}
		fade = ( ( backEnd.refdef.time - f->fadeTime ) /1000.0f ) * r_flareFade->value;
	} else {
		if ( f->visible ) {
			f->visible = qfalse;
			f->fadeTime = backEnd.refdef.time - 1;
		}
		fade = 1.0f - ( ( backEnd.refdef.time - f->fadeTime ) / 1000.0f ) * r_flareFade->value;
	}

	if ( fade < 0 ) {
		fade = 0;
	}
	if ( fade > 1 ) {
		fade = 1;
	}

	f->drawIntensity = fade;
}