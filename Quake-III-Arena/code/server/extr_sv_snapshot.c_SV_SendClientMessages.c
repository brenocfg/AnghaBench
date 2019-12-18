#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ unsentFragmentStart; scalar_t__ unsentLength; scalar_t__ unsentFragments; } ;
struct TYPE_9__ {scalar_t__ nextSnapshotTime; TYPE_1__ netchan; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ client_t ;
struct TYPE_11__ {int integer; } ;
struct TYPE_10__ {scalar_t__ time; TYPE_2__* clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  SV_Netchan_TransmitNextFragment (TYPE_2__*) ; 
 scalar_t__ SV_RateMsec (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  SV_SendClientSnapshot (TYPE_2__*) ; 
 TYPE_4__* sv_maxclients ; 
 TYPE_3__ svs ; 

void SV_SendClientMessages( void ) {
	int			i;
	client_t	*c;

	// send a message to each connected client
	for (i=0, c = svs.clients ; i < sv_maxclients->integer ; i++, c++) {
		if (!c->state) {
			continue;		// not connected
		}

		if ( svs.time < c->nextSnapshotTime ) {
			continue;		// not time yet
		}

		// send additional message fragments if the last message
		// was too large to send at once
		if ( c->netchan.unsentFragments ) {
			c->nextSnapshotTime = svs.time + 
				SV_RateMsec( c, c->netchan.unsentLength - c->netchan.unsentFragmentStart );
			SV_Netchan_TransmitNextFragment( c );
			continue;
		}

		// generate and send a new message
		SV_SendClientSnapshot( c );
	}
}