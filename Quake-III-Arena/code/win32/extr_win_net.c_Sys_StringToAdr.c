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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  netadr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SockadrToNetadr (struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sys_StringToSockaddr (char const*,struct sockaddr*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean Sys_StringToAdr( const char *s, netadr_t *a ) {
	struct sockaddr sadr;
	
	if ( !Sys_StringToSockaddr( s, &sadr ) ) {
		return qfalse;
	}
	
	SockadrToNetadr( &sadr, a );
	return qtrue;
}