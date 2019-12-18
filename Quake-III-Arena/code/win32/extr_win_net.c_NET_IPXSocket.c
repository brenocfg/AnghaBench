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
struct sockaddr_ipx {scalar_t__ sa_socket; int /*<<< orphan*/  sa_nodenum; int /*<<< orphan*/  sa_netnum; int /*<<< orphan*/  sa_family; } ;
typedef  int /*<<< orphan*/  address ;
typedef  int /*<<< orphan*/  _true ;
typedef  int SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IPX ; 
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIONBIO ; 
 int INVALID_SOCKET ; 
 int /*<<< orphan*/  NET_ErrorString () ; 
 int /*<<< orphan*/  NSPROTO_IPX ; 
 int PORT_ANY ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 int WSAEAFNOSUPPORT ; 
 int WSAGetLastError () ; 
 scalar_t__ bind (int,void*,int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ htons (short) ; 
 scalar_t__ ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int NET_IPXSocket( int port ) {
	SOCKET				newsocket;
	struct sockaddr_ipx	address;
	int					_true = 1;
	int					err;

	if( ( newsocket = socket( AF_IPX, SOCK_DGRAM, NSPROTO_IPX ) ) == INVALID_SOCKET ) {
		err = WSAGetLastError();
		if (err != WSAEAFNOSUPPORT) {
			Com_Printf( "WARNING: IPX_Socket: socket: %s\n", NET_ErrorString() );
		}
		return 0;
	}

	// make it non-blocking
	if( ioctlsocket( newsocket, FIONBIO, &_true ) == SOCKET_ERROR ) {
		Com_Printf( "WARNING: IPX_Socket: ioctl FIONBIO: %s\n", NET_ErrorString() );
		return 0;
	}

	// make it broadcast capable
	if( setsockopt( newsocket, SOL_SOCKET, SO_BROADCAST, (char *)&_true, sizeof( _true ) ) == SOCKET_ERROR ) {
		Com_Printf( "WARNING: IPX_Socket: setsockopt SO_BROADCAST: %s\n", NET_ErrorString() );
		return 0;
	}

	address.sa_family = AF_IPX;
	memset( address.sa_netnum, 0, 4 );
	memset( address.sa_nodenum, 0, 6 );
	if( port == PORT_ANY ) {
		address.sa_socket = 0;
	}
	else {
		address.sa_socket = htons( (short)port );
	}

	if( bind( newsocket, (void *)&address, sizeof(address) ) == SOCKET_ERROR ) {
		Com_Printf( "WARNING: IPX_Socket: bind: %s\n", NET_ErrorString() );
		closesocket( newsocket );
		return 0;
	}

	return newsocket;
}