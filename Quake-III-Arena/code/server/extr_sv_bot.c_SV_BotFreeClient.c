#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* gentity; scalar_t__* name; int /*<<< orphan*/  state; } ;
typedef  TYPE_3__ client_t ;
struct TYPE_10__ {int integer; } ;
struct TYPE_9__ {TYPE_3__* clients; } ;
struct TYPE_6__ {int /*<<< orphan*/  svFlags; } ;
struct TYPE_7__ {TYPE_1__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_FREE ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  SVF_BOT ; 
 TYPE_5__* sv_maxclients ; 
 TYPE_4__ svs ; 

void SV_BotFreeClient( int clientNum ) {
	client_t	*cl;

	if ( clientNum < 0 || clientNum >= sv_maxclients->integer ) {
		Com_Error( ERR_DROP, "SV_BotFreeClient: bad clientNum: %i", clientNum );
	}
	cl = &svs.clients[clientNum];
	cl->state = CS_FREE;
	cl->name[0] = 0;
	if ( cl->gentity ) {
		cl->gentity->r.svFlags &= ~SVF_BOT;
	}
}