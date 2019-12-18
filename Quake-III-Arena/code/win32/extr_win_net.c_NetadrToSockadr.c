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
struct sockaddr_ipx {int /*<<< orphan*/  sa_socket; struct sockaddr* sa_nodenum; struct sockaddr* sa_netnum; void* sa_family; } ;
struct TYPE_4__ {int s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; void* sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  port; int /*<<< orphan*/ * ipx; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ netadr_t ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_IPX ; 
 int INADDR_BROADCAST ; 
 scalar_t__ NA_BROADCAST ; 
 scalar_t__ NA_BROADCAST_IPX ; 
 scalar_t__ NA_IP ; 
 scalar_t__ NA_IPX ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int,int) ; 

void NetadrToSockadr( netadr_t *a, struct sockaddr *s ) {
	memset( s, 0, sizeof(*s) );

	if( a->type == NA_BROADCAST ) {
		((struct sockaddr_in *)s)->sin_family = AF_INET;
		((struct sockaddr_in *)s)->sin_port = a->port;
		((struct sockaddr_in *)s)->sin_addr.s_addr = INADDR_BROADCAST;
	}
	else if( a->type == NA_IP ) {
		((struct sockaddr_in *)s)->sin_family = AF_INET;
		((struct sockaddr_in *)s)->sin_addr.s_addr = *(int *)&a->ip;
		((struct sockaddr_in *)s)->sin_port = a->port;
	}
	else if( a->type == NA_IPX ) {
		((struct sockaddr_ipx *)s)->sa_family = AF_IPX;
		memcpy( ((struct sockaddr_ipx *)s)->sa_netnum, &a->ipx[0], 4 );
		memcpy( ((struct sockaddr_ipx *)s)->sa_nodenum, &a->ipx[4], 6 );
		((struct sockaddr_ipx *)s)->sa_socket = a->port;
	}
	else if( a->type == NA_BROADCAST_IPX ) {
		((struct sockaddr_ipx *)s)->sa_family = AF_IPX;
		memset( ((struct sockaddr_ipx *)s)->sa_netnum, 0, 4 );
		memset( ((struct sockaddr_ipx *)s)->sa_nodenum, 0xff, 6 );
		((struct sockaddr_ipx *)s)->sa_socket = a->port;
	}
}