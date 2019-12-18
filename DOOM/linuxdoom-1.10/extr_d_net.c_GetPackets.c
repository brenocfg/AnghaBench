#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ticcmd_t ;
struct TYPE_6__ {int remotenode; } ;
struct TYPE_5__ {int checksum; int player; int numtics; int /*<<< orphan*/ * cmds; int /*<<< orphan*/  retransmitfrom; int /*<<< orphan*/  starttic; } ;
struct TYPE_4__ {int* message; } ;

/* Variables and functions */
 int BACKUPTICS ; 
 int ExpandTics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CheckDemoStatus () ; 
 scalar_t__ HGetPacket () ; 
 int /*<<< orphan*/  I_Error (char*) ; 
 int NCMD_EXIT ; 
 int NCMD_KILL ; 
 int NCMD_RETRANSMIT ; 
 int NCMD_SETUP ; 
 int PL_DRONE ; 
 scalar_t__ RESENDCOUNT ; 
 size_t consoleplayer ; 
 scalar_t__ debugfile ; 
 scalar_t__ demorecording ; 
 TYPE_3__* doomcom ; 
 int* exitmsg ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,...) ; 
 TYPE_2__* netbuffer ; 
 int /*<<< orphan*/ ** netcmds ; 
 int* nettics ; 
 int* nodeforplayer ; 
 int* nodeingame ; 
 int* playeringame ; 
 TYPE_1__* players ; 
 int* remoteresend ; 
 scalar_t__* resendcount ; 
 int* resendto ; 
 int /*<<< orphan*/  strcpy (int*,char*) ; 

void GetPackets (void)
{
    int		netconsole;
    int		netnode;
    ticcmd_t	*src, *dest;
    int		realend;
    int		realstart;
				 
    while ( HGetPacket() )
    {
	if (netbuffer->checksum & NCMD_SETUP)
	    continue;		// extra setup packet
			
	netconsole = netbuffer->player & ~PL_DRONE;
	netnode = doomcom->remotenode;
	
	// to save bytes, only the low byte of tic numbers are sent
	// Figure out what the rest of the bytes are
	realstart = ExpandTics (netbuffer->starttic);		
	realend = (realstart+netbuffer->numtics);
	
	// check for exiting the game
	if (netbuffer->checksum & NCMD_EXIT)
	{
	    if (!nodeingame[netnode])
		continue;
	    nodeingame[netnode] = false;
	    playeringame[netconsole] = false;
	    strcpy (exitmsg, "Player 1 left the game");
	    exitmsg[7] += netconsole;
	    players[consoleplayer].message = exitmsg;
	    if (demorecording)
		G_CheckDemoStatus ();
	    continue;
	}
	
	// check for a remote game kill
	if (netbuffer->checksum & NCMD_KILL)
	    I_Error ("Killed by network driver");

	nodeforplayer[netconsole] = netnode;
	
	// check for retransmit request
	if ( resendcount[netnode] <= 0 
	     && (netbuffer->checksum & NCMD_RETRANSMIT) )
	{
	    resendto[netnode] = ExpandTics(netbuffer->retransmitfrom);
	    if (debugfile)
		fprintf (debugfile,"retransmit from %i\n", resendto[netnode]);
	    resendcount[netnode] = RESENDCOUNT;
	}
	else
	    resendcount[netnode]--;
	
	// check for out of order / duplicated packet		
	if (realend == nettics[netnode])
	    continue;
			
	if (realend < nettics[netnode])
	{
	    if (debugfile)
		fprintf (debugfile,
			 "out of order packet (%i + %i)\n" ,
			 realstart,netbuffer->numtics);
	    continue;
	}
	
	// check for a missed packet
	if (realstart > nettics[netnode])
	{
	    // stop processing until the other system resends the missed tics
	    if (debugfile)
		fprintf (debugfile,
			 "missed tics from %i (%i - %i)\n",
			 netnode, realstart, nettics[netnode]);
	    remoteresend[netnode] = true;
	    continue;
	}

	// update command store from the packet
        {
	    int		start;

	    remoteresend[netnode] = false;
		
	    start = nettics[netnode] - realstart;		
	    src = &netbuffer->cmds[start];

	    while (nettics[netnode] < realend)
	    {
		dest = &netcmds[netconsole][nettics[netnode]%BACKUPTICS];
		nettics[netnode]++;
		*dest = *src;
		src++;
	    }
	}
    }
}