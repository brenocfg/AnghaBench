#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numnodes; int extratics; } ;
struct TYPE_3__ {int starttic; int numtics; scalar_t__ retransmitfrom; int /*<<< orphan*/ * cmds; int /*<<< orphan*/  player; } ;

/* Variables and functions */
 int BACKUPTICS ; 
 int /*<<< orphan*/  D_ProcessEvents () ; 
 int /*<<< orphan*/  G_BuildTiccmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetPackets () ; 
 int /*<<< orphan*/  HSendPacket (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I_Error (char*) ; 
 int I_GetTime () ; 
 int /*<<< orphan*/  I_StartTic () ; 
 int /*<<< orphan*/  NCMD_RETRANSMIT ; 
 int /*<<< orphan*/  consoleplayer ; 
 TYPE_2__* doomcom ; 
 int gametic ; 
 int gametime ; 
 int /*<<< orphan*/ * localcmds ; 
 int maketic ; 
 TYPE_1__* netbuffer ; 
 scalar_t__* nettics ; 
 scalar_t__* nodeingame ; 
 scalar_t__* remoteresend ; 
 int* resendto ; 
 scalar_t__ singletics ; 
 int skiptics ; 
 int ticdup ; 

void NetUpdate (void)
{
    int             nowtime;
    int             newtics;
    int				i,j;
    int				realstart;
    int				gameticdiv;
    
    // check time
    nowtime = I_GetTime ()/ticdup;
    newtics = nowtime - gametime;
    gametime = nowtime;
	
    if (newtics <= 0) 	// nothing new to update
	goto listen; 

    if (skiptics <= newtics)
    {
	newtics -= skiptics;
	skiptics = 0;
    }
    else
    {
	skiptics -= newtics;
	newtics = 0;
    }
	
		
    netbuffer->player = consoleplayer;
    
    // build new ticcmds for console player
    gameticdiv = gametic/ticdup;
    for (i=0 ; i<newtics ; i++)
    {
	I_StartTic ();
	D_ProcessEvents ();
	if (maketic - gameticdiv >= BACKUPTICS/2-1)
	    break;          // can't hold any more
	
	//printf ("mk:%i ",maketic);
	G_BuildTiccmd (&localcmds[maketic%BACKUPTICS]);
	maketic++;
    }


    if (singletics)
	return;         // singletic update is syncronous
    
    // send the packet to the other nodes
    for (i=0 ; i<doomcom->numnodes ; i++)
	if (nodeingame[i])
	{
	    netbuffer->starttic = realstart = resendto[i];
	    netbuffer->numtics = maketic - realstart;
	    if (netbuffer->numtics > BACKUPTICS)
		I_Error ("NetUpdate: netbuffer->numtics > BACKUPTICS");

	    resendto[i] = maketic - doomcom->extratics;

	    for (j=0 ; j< netbuffer->numtics ; j++)
		netbuffer->cmds[j] = 
		    localcmds[(realstart+j)%BACKUPTICS];
					
	    if (remoteresend[i])
	    {
		netbuffer->retransmitfrom = nettics[i];
		HSendPacket (i, NCMD_RETRANSMIT);
	    }
	    else
	    {
		netbuffer->retransmitfrom = 0;
		HSendPacket (i, 0);
	    }
	}
    
    // listen for other packets
  listen:
    GetPackets ();
}