#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  GAMESERVER_BACK0 ; 
 int /*<<< orphan*/  GAMESERVER_BACK1 ; 
 int /*<<< orphan*/  GAMESERVER_FIGHT0 ; 
 int /*<<< orphan*/  GAMESERVER_FIGHT1 ; 
 int /*<<< orphan*/  GAMESERVER_SELECT ; 
 int /*<<< orphan*/  GAMESERVER_UNKNOWNMAP ; 
 int /*<<< orphan*/  trap_R_RegisterShaderNoMip (int /*<<< orphan*/ ) ; 

void ServerOptions_Cache( void ) {
	trap_R_RegisterShaderNoMip( GAMESERVER_BACK0 );
	trap_R_RegisterShaderNoMip( GAMESERVER_BACK1 );
	trap_R_RegisterShaderNoMip( GAMESERVER_FIGHT0 );
	trap_R_RegisterShaderNoMip( GAMESERVER_FIGHT1 );
	trap_R_RegisterShaderNoMip( GAMESERVER_SELECT );
	trap_R_RegisterShaderNoMip( GAMESERVER_UNKNOWNMAP );
}