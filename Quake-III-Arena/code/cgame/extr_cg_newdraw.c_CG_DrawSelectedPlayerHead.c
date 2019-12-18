#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  double* vec3_t ;
struct TYPE_9__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ rectDef_t ;
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  clipHandle_t ;
struct TYPE_10__ {scalar_t__ deferred; int /*<<< orphan*/  modelIcon; int /*<<< orphan*/  headSkin; int /*<<< orphan*/  headModel; int /*<<< orphan*/  headOffset; } ;
typedef  TYPE_3__ clientInfo_t ;
struct TYPE_13__ {scalar_t__ integer; } ;
struct TYPE_12__ {scalar_t__ integer; } ;
struct TYPE_8__ {int /*<<< orphan*/  deferShader; } ;
struct TYPE_11__ {int currentVoiceClient; TYPE_1__ media; TYPE_3__* clientinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Draw3DModel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,double*) ; 
 int /*<<< orphan*/  CG_DrawPic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t CG_GetSelectedPlayer () ; 
 size_t PITCH ; 
 size_t ROLL ; 
 int /*<<< orphan*/  VectorAdd (double*,int /*<<< orphan*/ ,double*) ; 
 size_t YAW ; 
 TYPE_6__ cg_draw3dIcons ; 
 TYPE_5__ cg_drawIcons ; 
 TYPE_4__ cgs ; 
 int* sortedTeamPlayers ; 
 int /*<<< orphan*/  trap_R_ModelBounds (int /*<<< orphan*/ ,double*,double*) ; 

__attribute__((used)) static void CG_DrawSelectedPlayerHead( rectDef_t *rect, qboolean draw2D, qboolean voice ) {
	clipHandle_t	cm;
	clientInfo_t	*ci;
	float			len;
	vec3_t			origin;
	vec3_t			mins, maxs, angles;


  ci = cgs.clientinfo + ((voice) ? cgs.currentVoiceClient : sortedTeamPlayers[CG_GetSelectedPlayer()]);

  if (ci) {
  	if ( cg_draw3dIcons.integer ) {
	  	cm = ci->headModel;
  		if ( !cm ) {
  			return;
	  	}

  		// offset the origin y and z to center the head
  		trap_R_ModelBounds( cm, mins, maxs );

	  	origin[2] = -0.5 * ( mins[2] + maxs[2] );
  		origin[1] = 0.5 * ( mins[1] + maxs[1] );

	  	// calculate distance so the head nearly fills the box
  		// assume heads are taller than wide
  		len = 0.7 * ( maxs[2] - mins[2] );		
  		origin[0] = len / 0.268;	// len / tan( fov/2 )

  		// allow per-model tweaking
  		VectorAdd( origin, ci->headOffset, origin );

    	angles[PITCH] = 0;
    	angles[YAW] = 180;
    	angles[ROLL] = 0;
  	
      CG_Draw3DModel( rect->x, rect->y, rect->w, rect->h, ci->headModel, ci->headSkin, origin, angles );
  	} else if ( cg_drawIcons.integer ) {
	  	CG_DrawPic( rect->x, rect->y, rect->w, rect->h, ci->modelIcon );
  	}

  	// if they are deferred, draw a cross out
  	if ( ci->deferred ) {
  		CG_DrawPic( rect->x, rect->y, rect->w, rect->h, cgs.media.deferShader );
  	}
  }

}