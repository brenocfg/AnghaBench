#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int integer; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ cvar_t ;
struct TYPE_5__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVAR_LATCH ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 TYPE_1__* Cvar_Get (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_SetValue (char*,int) ; 
 int /*<<< orphan*/  NET_GetLocalAddress () ; 
 scalar_t__ NET_IPSocket (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NET_OpenSocks (int) ; 
 int /*<<< orphan*/  PORT_SERVER ; 
 scalar_t__ ip_socket ; 
 TYPE_2__* net_socksEnabled ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

void NET_OpenIP( void ) {
	cvar_t	*ip;
	int		port;
	int		i;

	ip = Cvar_Get( "net_ip", "localhost", CVAR_LATCH );
	port = Cvar_Get( "net_port", va( "%i", PORT_SERVER ), CVAR_LATCH )->integer;

	// automatically scan for a valid port, so multiple
	// dedicated servers can be started without requiring
	// a different net_port for each one
	for( i = 0 ; i < 10 ; i++ ) {
		ip_socket = NET_IPSocket( ip->string, port + i );
		if ( ip_socket ) {
			Cvar_SetValue( "net_port", port + i );
			if ( net_socksEnabled->integer ) {
				NET_OpenSocks( port + i );
			}
			NET_GetLocalAddress();
			return;
		}
	}
	Com_Printf( "WARNING: Couldn't allocate IP port\n");
}