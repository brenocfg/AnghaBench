#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ netadr_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 scalar_t__ NA_BROADCAST ; 
 scalar_t__ NA_BROADCAST_IPX ; 
 scalar_t__ NA_IP ; 
 scalar_t__ NA_IPX ; 
 int /*<<< orphan*/  NET_AdrToString (TYPE_1__) ; 
 int /*<<< orphan*/  NET_ErrorString () ; 
 int /*<<< orphan*/  NetadrToSockadr (TYPE_1__*,struct sockaddr_in*) ; 
 int ip_socket ; 
 int ipx_socket ; 
 int sendto (int,void const*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

void	Sys_SendPacket( int length, const void *data, netadr_t to )
{
	int		ret;
	struct sockaddr_in	addr;
	int		net_socket;

	if (to.type == NA_BROADCAST)
	{
		net_socket = ip_socket;
	}
	else if (to.type == NA_IP)
	{
		net_socket = ip_socket;
	}
	else if (to.type == NA_IPX)
	{
		net_socket = ipx_socket;
	}
	else if (to.type == NA_BROADCAST_IPX)
	{
		net_socket = ipx_socket;
	}
	else {
		Com_Error (ERR_FATAL, "NET_SendPacket: bad address type");
		return;
	}

	if (!net_socket)
		return;

	NetadrToSockadr (&to, &addr);

	ret = sendto (net_socket, data, length, 0, (struct sockaddr *)&addr, sizeof(addr) );
	if (ret == -1)
	{
		Com_Printf ("NET_SendPacket ERROR: %s to %s\n", NET_ErrorString(),
				NET_AdrToString (to));
	}
}