#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_14__ {TYPE_2__* client; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_17__ {scalar_t__ integer; } ;
struct TYPE_16__ {scalar_t__ integer; } ;
struct TYPE_15__ {int maxclients; } ;
struct TYPE_12__ {int /*<<< orphan*/  netname; } ;
struct TYPE_13__ {TYPE_1__ pers; } ;

/* Variables and functions */
 scalar_t__ GT_TEAM ; 
 int /*<<< orphan*/  G_Printf (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  G_VoiceTo (TYPE_3__*,TYPE_3__*,int,char const*,int /*<<< orphan*/ ) ; 
 int SAY_ALL ; 
 int SAY_TEAM ; 
 TYPE_7__ g_dedicated ; 
 TYPE_3__* g_entities ; 
 TYPE_5__ g_gametype ; 
 TYPE_4__ level ; 

void G_Voice( gentity_t *ent, gentity_t *target, int mode, const char *id, qboolean voiceonly ) {
	int			j;
	gentity_t	*other;

	if ( g_gametype.integer < GT_TEAM && mode == SAY_TEAM ) {
		mode = SAY_ALL;
	}

	if ( target ) {
		G_VoiceTo( ent, target, mode, id, voiceonly );
		return;
	}

	// echo the text to the console
	if ( g_dedicated.integer ) {
		G_Printf( "voice: %s %s\n", ent->client->pers.netname, id);
	}

	// send it to all the apropriate clients
	for (j = 0; j < level.maxclients; j++) {
		other = &g_entities[j];
		G_VoiceTo( ent, other, mode, id, voiceonly );
	}
}