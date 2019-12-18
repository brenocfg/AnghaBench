#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int count; TYPE_1__* item; } ;
typedef  TYPE_2__ gentity_t ;
struct TYPE_6__ {int quantity; int /*<<< orphan*/  giTag; } ;

/* Variables and functions */
 int /*<<< orphan*/  Add_Ammo (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int RESPAWN_AMMO ; 

int Pickup_Ammo (gentity_t *ent, gentity_t *other)
{
	int		quantity;

	if ( ent->count ) {
		quantity = ent->count;
	} else {
		quantity = ent->item->quantity;
	}

	Add_Ammo (other, ent->item->giTag, quantity);

	return RESPAWN_AMMO;
}