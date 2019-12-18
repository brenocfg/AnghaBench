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
 int /*<<< orphan*/  ART_ARROWS0 ; 
 int /*<<< orphan*/  ART_ARROWS_DOWN ; 
 int /*<<< orphan*/  ART_ARROWS_UP ; 
 int /*<<< orphan*/  ART_BACK0 ; 
 int /*<<< orphan*/  ART_BACK1 ; 
 int /*<<< orphan*/  ART_CONNECT0 ; 
 int /*<<< orphan*/  ART_CONNECT1 ; 
 int /*<<< orphan*/  ART_CREATE0 ; 
 int /*<<< orphan*/  ART_CREATE1 ; 
 int /*<<< orphan*/  ART_PUNKBUSTER ; 
 int /*<<< orphan*/  ART_REFRESH0 ; 
 int /*<<< orphan*/  ART_REFRESH1 ; 
 int /*<<< orphan*/  ART_SPECIFY0 ; 
 int /*<<< orphan*/  ART_SPECIFY1 ; 
 int /*<<< orphan*/  ART_UNKNOWNMAP ; 
 int /*<<< orphan*/  trap_R_RegisterShaderNoMip (int /*<<< orphan*/ ) ; 

void ArenaServers_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	trap_R_RegisterShaderNoMip( ART_CREATE0 );
	trap_R_RegisterShaderNoMip( ART_CREATE1 );
	trap_R_RegisterShaderNoMip( ART_SPECIFY0 );
	trap_R_RegisterShaderNoMip( ART_SPECIFY1 );
	trap_R_RegisterShaderNoMip( ART_REFRESH0 );
	trap_R_RegisterShaderNoMip( ART_REFRESH1 );
	trap_R_RegisterShaderNoMip( ART_CONNECT0 );
	trap_R_RegisterShaderNoMip( ART_CONNECT1 );
	trap_R_RegisterShaderNoMip( ART_ARROWS0  );
	trap_R_RegisterShaderNoMip( ART_ARROWS_UP );
	trap_R_RegisterShaderNoMip( ART_ARROWS_DOWN );
	trap_R_RegisterShaderNoMip( ART_UNKNOWNMAP );
	trap_R_RegisterShaderNoMip( ART_PUNKBUSTER );
}