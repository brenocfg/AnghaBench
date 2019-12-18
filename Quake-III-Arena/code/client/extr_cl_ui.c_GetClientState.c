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
struct TYPE_10__ {int /*<<< orphan*/  clientNum; int /*<<< orphan*/  messageString; int /*<<< orphan*/  updateInfoString; int /*<<< orphan*/  servername; int /*<<< orphan*/  connState; int /*<<< orphan*/  connectPacketCount; } ;
typedef  TYPE_3__ uiClientState_t ;
struct TYPE_8__ {int /*<<< orphan*/  clientNum; } ;
struct TYPE_9__ {TYPE_1__ ps; } ;
struct TYPE_13__ {TYPE_2__ snap; } ;
struct TYPE_12__ {int /*<<< orphan*/  serverMessage; int /*<<< orphan*/  connectPacketCount; } ;
struct TYPE_11__ {int /*<<< orphan*/  updateInfoString; int /*<<< orphan*/  servername; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_6__ cl ; 
 TYPE_5__ clc ; 
 TYPE_4__ cls ; 

__attribute__((used)) static void GetClientState( uiClientState_t *state ) {
	state->connectPacketCount = clc.connectPacketCount;
	state->connState = cls.state;
	Q_strncpyz( state->servername, cls.servername, sizeof( state->servername ) );
	Q_strncpyz( state->updateInfoString, cls.updateInfoString, sizeof( state->updateInfoString ) );
	Q_strncpyz( state->messageString, clc.serverMessage, sizeof( state->messageString ) );
	state->clientNum = cl.snap.ps.clientNum;
}