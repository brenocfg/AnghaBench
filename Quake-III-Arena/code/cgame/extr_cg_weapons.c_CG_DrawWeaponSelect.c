#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__* stats; } ;
struct TYPE_16__ {int weaponSelect; TYPE_3__* snap; scalar_t__ itemPickupTime; int /*<<< orphan*/  weaponSelectTime; TYPE_1__ predictedPlayerState; } ;
struct TYPE_15__ {TYPE_5__* item; int /*<<< orphan*/  weaponIcon; } ;
struct TYPE_12__ {int /*<<< orphan*/  noammoShader; int /*<<< orphan*/  selectShader; } ;
struct TYPE_14__ {TYPE_4__ media; } ;
struct TYPE_13__ {char* pickup_name; } ;
struct TYPE_10__ {int* stats; int /*<<< orphan*/ * ammo; } ;
struct TYPE_11__ {TYPE_2__ ps; } ;

/* Variables and functions */
 int BIGCHAR_WIDTH ; 
 int /*<<< orphan*/  CG_DrawBigStringColor (int,int,char*,float*) ; 
 int /*<<< orphan*/  CG_DrawPic (int,int,int,int,int /*<<< orphan*/ ) ; 
 int CG_DrawStrlen (char*) ; 
 float* CG_FadeColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_RegisterWeapon (int) ; 
 int SCREEN_WIDTH ; 
 size_t STAT_HEALTH ; 
 size_t STAT_WEAPONS ; 
 int /*<<< orphan*/  WEAPON_SELECT_TIME ; 
 TYPE_8__ cg ; 
 TYPE_7__* cg_weapons ; 
 TYPE_6__ cgs ; 
 int /*<<< orphan*/  trap_R_SetColor (float*) ; 

void CG_DrawWeaponSelect( void ) {
	int		i;
	int		bits;
	int		count;
	int		x, y, w;
	char	*name;
	float	*color;

	// don't display if dead
	if ( cg.predictedPlayerState.stats[STAT_HEALTH] <= 0 ) {
		return;
	}

	color = CG_FadeColor( cg.weaponSelectTime, WEAPON_SELECT_TIME );
	if ( !color ) {
		return;
	}
	trap_R_SetColor( color );

	// showing weapon select clears pickup item display, but not the blend blob
	cg.itemPickupTime = 0;

	// count the number of weapons owned
	bits = cg.snap->ps.stats[ STAT_WEAPONS ];
	count = 0;
	for ( i = 1 ; i < 16 ; i++ ) {
		if ( bits & ( 1 << i ) ) {
			count++;
		}
	}

	x = 320 - count * 20;
	y = 380;

	for ( i = 1 ; i < 16 ; i++ ) {
		if ( !( bits & ( 1 << i ) ) ) {
			continue;
		}

		CG_RegisterWeapon( i );

		// draw weapon icon
		CG_DrawPic( x, y, 32, 32, cg_weapons[i].weaponIcon );

		// draw selection marker
		if ( i == cg.weaponSelect ) {
			CG_DrawPic( x-4, y-4, 40, 40, cgs.media.selectShader );
		}

		// no ammo cross on top
		if ( !cg.snap->ps.ammo[ i ] ) {
			CG_DrawPic( x, y, 32, 32, cgs.media.noammoShader );
		}

		x += 40;
	}

	// draw the selected name
	if ( cg_weapons[ cg.weaponSelect ].item ) {
		name = cg_weapons[ cg.weaponSelect ].item->pickup_name;
		if ( name ) {
			w = CG_DrawStrlen( name ) * BIGCHAR_WIDTH;
			x = ( SCREEN_WIDTH - w ) / 2;
			CG_DrawBigStringColor(x, y - 22, name, color);
		}
	}

	trap_R_SetColor( NULL );
}