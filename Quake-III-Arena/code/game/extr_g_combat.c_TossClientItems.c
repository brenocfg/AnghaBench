#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gitem_t ;
struct TYPE_12__ {int weapon; } ;
struct TYPE_17__ {int count; TYPE_5__* client; TYPE_1__ s; } ;
typedef  TYPE_6__ gentity_t ;
struct TYPE_19__ {scalar_t__ integer; } ;
struct TYPE_18__ {scalar_t__ time; } ;
struct TYPE_15__ {scalar_t__ weaponstate; int* stats; scalar_t__* powerups; scalar_t__* ammo; } ;
struct TYPE_13__ {int weapon; } ;
struct TYPE_14__ {TYPE_2__ cmd; } ;
struct TYPE_16__ {TYPE_4__ ps; TYPE_3__ pers; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BG_FindItemForPowerup (int) ; 
 int /*<<< orphan*/ * BG_FindItemForWeapon (int) ; 
 TYPE_6__* Drop_Item (TYPE_6__*,int /*<<< orphan*/ *,float) ; 
 scalar_t__ GT_TEAM ; 
 int PW_NUM_POWERUPS ; 
 size_t STAT_WEAPONS ; 
 scalar_t__ WEAPON_DROPPING ; 
 int WP_GRAPPLING_HOOK ; 
 int WP_MACHINEGUN ; 
 int WP_NONE ; 
 TYPE_8__ g_gametype ; 
 TYPE_7__ level ; 

void TossClientItems( gentity_t *self ) {
	gitem_t		*item;
	int			weapon;
	float		angle;
	int			i;
	gentity_t	*drop;

	// drop the weapon if not a gauntlet or machinegun
	weapon = self->s.weapon;

	// make a special check to see if they are changing to a new
	// weapon that isn't the mg or gauntlet.  Without this, a client
	// can pick up a weapon, be killed, and not drop the weapon because
	// their weapon change hasn't completed yet and they are still holding the MG.
	if ( weapon == WP_MACHINEGUN || weapon == WP_GRAPPLING_HOOK ) {
		if ( self->client->ps.weaponstate == WEAPON_DROPPING ) {
			weapon = self->client->pers.cmd.weapon;
		}
		if ( !( self->client->ps.stats[STAT_WEAPONS] & ( 1 << weapon ) ) ) {
			weapon = WP_NONE;
		}
	}

	if ( weapon > WP_MACHINEGUN && weapon != WP_GRAPPLING_HOOK && 
		self->client->ps.ammo[ weapon ] ) {
		// find the item type for this weapon
		item = BG_FindItemForWeapon( weapon );

		// spawn the item
		Drop_Item( self, item, 0 );
	}

	// drop all the powerups if not in teamplay
	if ( g_gametype.integer != GT_TEAM ) {
		angle = 45;
		for ( i = 1 ; i < PW_NUM_POWERUPS ; i++ ) {
			if ( self->client->ps.powerups[ i ] > level.time ) {
				item = BG_FindItemForPowerup( i );
				if ( !item ) {
					continue;
				}
				drop = Drop_Item( self, item, angle );
				// decide how many seconds it has left
				drop->count = ( self->client->ps.powerups[ i ] - level.time ) / 1000;
				if ( drop->count < 1 ) {
					drop->count = 1;
				}
				angle += 45;
			}
		}
	}
}