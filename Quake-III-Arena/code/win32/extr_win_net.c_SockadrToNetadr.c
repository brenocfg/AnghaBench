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
struct sockaddr_ipx {int /*<<< orphan*/  sa_socket; int /*<<< orphan*/  sa_nodenum; int /*<<< orphan*/  sa_netnum; } ;
struct TYPE_4__ {int s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_5__ {int /*<<< orphan*/  port; int /*<<< orphan*/ * ipx; int /*<<< orphan*/  type; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ netadr_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_IPX ; 
 int /*<<< orphan*/  NA_IP ; 
 int /*<<< orphan*/  NA_IPX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void SockadrToNetadr( struct sockaddr *s, netadr_t *a ) {
	if (s->sa_family == AF_INET) {
		a->type = NA_IP;
		*(int *)&a->ip = ((struct sockaddr_in *)s)->sin_addr.s_addr;
		a->port = ((struct sockaddr_in *)s)->sin_port;
	}
	else if( s->sa_family == AF_IPX ) {
		a->type = NA_IPX;
		memcpy( &a->ipx[0], ((struct sockaddr_ipx *)s)->sa_netnum, 4 );
		memcpy( &a->ipx[4], ((struct sockaddr_ipx *)s)->sa_nodenum, 6 );
		a->port = ((struct sockaddr_ipx *)s)->sa_socket;
	}
}