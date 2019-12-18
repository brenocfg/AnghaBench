#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sw ;
struct TYPE_10__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  fromaddress ;
struct TYPE_14__ {int numtics; TYPE_4__* cmds; int /*<<< orphan*/  starttic; int /*<<< orphan*/  retransmitfrom; int /*<<< orphan*/  player; int /*<<< orphan*/  checksum; } ;
typedef  TYPE_5__ doomdata_t ;
struct TYPE_17__ {int remotenode; int numnodes; int datalength; } ;
struct TYPE_16__ {int numtics; TYPE_3__* cmds; int /*<<< orphan*/  starttic; int /*<<< orphan*/  retransmitfrom; int /*<<< orphan*/  player; int /*<<< orphan*/  checksum; } ;
struct TYPE_11__ {scalar_t__ s_addr; } ;
struct TYPE_15__ {TYPE_2__ sin_addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  buttons; int /*<<< orphan*/  chatchar; int /*<<< orphan*/  consistancy; int /*<<< orphan*/  angleturn; int /*<<< orphan*/  sidemove; int /*<<< orphan*/  forwardmove; } ;
struct TYPE_12__ {int /*<<< orphan*/  buttons; int /*<<< orphan*/  chatchar; void* consistancy; void* angleturn; int /*<<< orphan*/  sidemove; int /*<<< orphan*/  forwardmove; } ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  I_Error (char*,int /*<<< orphan*/ ) ; 
 TYPE_9__* doomcom ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  insocket ; 
 TYPE_8__* netbuffer ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int recvfrom (int /*<<< orphan*/ ,TYPE_5__*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 TYPE_6__* sendaddress ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

void PacketGet (void)
{
    int			i;
    int			c;
    struct sockaddr_in	fromaddress;
    int			fromlen;
    doomdata_t		sw;
				
    fromlen = sizeof(fromaddress);
    c = recvfrom (insocket, &sw, sizeof(sw), 0
		  , (struct sockaddr *)&fromaddress, &fromlen );
    if (c == -1 )
    {
	if (errno != EWOULDBLOCK)
	    I_Error ("GetPacket: %s",strerror(errno));
	doomcom->remotenode = -1;		// no packet
	return;
    }

    {
	static int first=1;
	if (first)
	    printf("len=%d:p=[0x%x 0x%x] \n", c, *(int*)&sw, *((int*)&sw+1));
	first = 0;
    }

    // find remote node number
    for (i=0 ; i<doomcom->numnodes ; i++)
	if ( fromaddress.sin_addr.s_addr == sendaddress[i].sin_addr.s_addr )
	    break;

    if (i == doomcom->numnodes)
    {
	// packet is not from one of the players (new game broadcast)
	doomcom->remotenode = -1;		// no packet
	return;
    }
	
    doomcom->remotenode = i;			// good packet from a game player
    doomcom->datalength = c;
	
    // byte swap
    netbuffer->checksum = ntohl(sw.checksum);
    netbuffer->player = sw.player;
    netbuffer->retransmitfrom = sw.retransmitfrom;
    netbuffer->starttic = sw.starttic;
    netbuffer->numtics = sw.numtics;

    for (c=0 ; c< netbuffer->numtics ; c++)
    {
	netbuffer->cmds[c].forwardmove = sw.cmds[c].forwardmove;
	netbuffer->cmds[c].sidemove = sw.cmds[c].sidemove;
	netbuffer->cmds[c].angleturn = ntohs(sw.cmds[c].angleturn);
	netbuffer->cmds[c].consistancy = ntohs(sw.cmds[c].consistancy);
	netbuffer->cmds[c].chatchar = sw.cmds[c].chatchar;
	netbuffer->cmds[c].buttons = sw.cmds[c].buttons;
    }
}