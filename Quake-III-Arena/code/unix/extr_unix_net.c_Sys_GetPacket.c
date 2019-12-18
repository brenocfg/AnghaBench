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
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  netadr_t ;
struct TYPE_3__ {int maxsize; int cursize; scalar_t__ readcount; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ msg_t ;
typedef  int /*<<< orphan*/  from ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ,...) ; 
 int ECONNREFUSED ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  NET_AdrToString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_ErrorString () ; 
 int /*<<< orphan*/  SockadrToNetadr (struct sockaddr_in*,int /*<<< orphan*/ *) ; 
 int errno ; 
 int ip_socket ; 
 int ipx_socket ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int recvfrom (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 

qboolean	Sys_GetPacket (netadr_t *net_from, msg_t *net_message)
{
	int 	ret;
	struct sockaddr_in	from;
	int		fromlen;
	int		net_socket;
	int		protocol;
	int		err;

	for (protocol = 0 ; protocol < 2 ; protocol++)
	{
		if (protocol == 0)
			net_socket = ip_socket;
		else
			net_socket = ipx_socket;

		if (!net_socket)
			continue;

		fromlen = sizeof(from);
		ret = recvfrom (net_socket, net_message->data, net_message->maxsize
			, 0, (struct sockaddr *)&from, &fromlen);

		SockadrToNetadr (&from, net_from);
		// bk000305: was missing
		net_message->readcount = 0;

		if (ret == -1)
		{
			err = errno;

			if (err == EWOULDBLOCK || err == ECONNREFUSED)
				continue;
			Com_Printf ("NET_GetPacket: %s from %s\n", NET_ErrorString(),
						NET_AdrToString(*net_from));
			continue;
		}

		if (ret == net_message->maxsize)
		{
			Com_Printf ("Oversize packet from %s\n", NET_AdrToString (*net_from));
			continue;
		}

		net_message->cursize = ret;
		return qtrue;
	}

	return qfalse;
}