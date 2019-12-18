#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int /*<<< orphan*/  sin_zero; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_7__ {int* ip; short port; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ netadr_t ;
struct TYPE_8__ {int* data; int maxsize; int readcount; int cursize; } ;
typedef  TYPE_2__ msg_t ;
typedef  int /*<<< orphan*/  from ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NA_IP ; 
 int /*<<< orphan*/  NET_AdrToString (TYPE_1__) ; 
 int /*<<< orphan*/  NET_ErrorString () ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  SockadrToNetadr (struct sockaddr*,TYPE_1__*) ; 
 int WSAECONNRESET ; 
 int WSAEWOULDBLOCK ; 
 int WSAGetLastError () ; 
 int ip_socket ; 
 int ipx_socket ; 
 scalar_t__ memcmp (struct sockaddr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int recvfrom (int,int*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  recvfromCount ; 
 int /*<<< orphan*/  socksRelayAddr ; 
 scalar_t__ usingSocks ; 

qboolean Sys_GetPacket( netadr_t *net_from, msg_t *net_message ) {
	int 	ret;
	struct sockaddr from;
	int		fromlen;
	int		net_socket;
	int		protocol;
	int		err;

	for( protocol = 0 ; protocol < 2 ; protocol++ )	{
		if( protocol == 0 ) {
			net_socket = ip_socket;
		}
		else {
			net_socket = ipx_socket;
		}

		if( !net_socket ) {
			continue;
		}

		fromlen = sizeof(from);
		recvfromCount++;		// performance check
		ret = recvfrom( net_socket, net_message->data, net_message->maxsize, 0, (struct sockaddr *)&from, &fromlen );
		if (ret == SOCKET_ERROR)
		{
			err = WSAGetLastError();

			if( err == WSAEWOULDBLOCK || err == WSAECONNRESET ) {
				continue;
			}
			Com_Printf( "NET_GetPacket: %s\n", NET_ErrorString() );
			continue;
		}

		if ( net_socket == ip_socket ) {
			memset( ((struct sockaddr_in *)&from)->sin_zero, 0, 8 );
		}

		if ( usingSocks && net_socket == ip_socket && memcmp( &from, &socksRelayAddr, fromlen ) == 0 ) {
			if ( ret < 10 || net_message->data[0] != 0 || net_message->data[1] != 0 || net_message->data[2] != 0 || net_message->data[3] != 1 ) {
				continue;
			}
			net_from->type = NA_IP;
			net_from->ip[0] = net_message->data[4];
			net_from->ip[1] = net_message->data[5];
			net_from->ip[2] = net_message->data[6];
			net_from->ip[3] = net_message->data[7];
			net_from->port = *(short *)&net_message->data[8];
			net_message->readcount = 10;
		}
		else {
			SockadrToNetadr( &from, net_from );
			net_message->readcount = 0;
		}

		if( ret == net_message->maxsize ) {
			Com_Printf( "Oversize packet from %s\n", NET_AdrToString (*net_from) );
			continue;
		}

		net_message->cursize = ret;
		return qtrue;
	}

	return qfalse;
}