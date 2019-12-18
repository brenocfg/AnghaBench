#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int value; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ cvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* Cvar_Get (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_SetValue (char*,int) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  NET_GetLocalAddress () ; 
 scalar_t__ NET_IPSocket (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PORT_SERVER ; 
 scalar_t__ ip_socket ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

void NET_OpenIP (void)
{
	cvar_t	*ip;
	int		port;
	int		i;

	ip = Cvar_Get ("net_ip", "localhost", 0);

	port = Cvar_Get("net_port", va("%i", PORT_SERVER), 0)->value;

	for ( i = 0 ; i < 10 ; i++ ) {
		ip_socket = NET_IPSocket (ip->string, port + i);
		if ( ip_socket ) {
			Cvar_SetValue( "net_port", port + i );
			NET_GetLocalAddress();
			return;
		}
	}
	Com_Error (ERR_FATAL, "Couldn't allocate IP port");
}