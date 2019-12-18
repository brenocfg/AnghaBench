#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ linked; } ;
struct TYPE_9__ {TYPE_1__ r; } ;
typedef  TYPE_2__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  trap_LinkEntity (TYPE_2__*) ; 
 int /*<<< orphan*/  trap_UnlinkEntity (TYPE_2__*) ; 

void hurt_use( gentity_t *self, gentity_t *other, gentity_t *activator ) {
	if ( self->r.linked ) {
		trap_UnlinkEntity( self );
	} else {
		trap_LinkEntity( self );
	}
}