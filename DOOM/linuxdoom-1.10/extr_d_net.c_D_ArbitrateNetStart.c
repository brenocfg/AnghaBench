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
typedef  int /*<<< orphan*/  gotinfo ;
typedef  int boolean ;
struct TYPE_4__ {int numnodes; scalar_t__ consoleplayer; } ;
struct TYPE_3__ {int checksum; int player; int retransmitfrom; int starttic; scalar_t__ numtics; } ;

/* Variables and functions */
 int /*<<< orphan*/  CheckAbort () ; 
 scalar_t__ HGetPacket () ; 
 int /*<<< orphan*/  HSendPacket (int,int) ; 
 int /*<<< orphan*/  I_Error (char*) ; 
 int MAXNETNODES ; 
 int NCMD_SETUP ; 
 int VERSION ; 
 int autostart ; 
 int deathmatch ; 
 TYPE_2__* doomcom ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* netbuffer ; 
 int nomonsters ; 
 int /*<<< orphan*/  printf (char*) ; 
 int respawnparm ; 
 int startepisode ; 
 int startmap ; 
 int startskill ; 

void D_ArbitrateNetStart (void)
{
    int		i;
    boolean	gotinfo[MAXNETNODES];
	
    autostart = true;
    memset (gotinfo,0,sizeof(gotinfo));
	
    if (doomcom->consoleplayer)
    {
	// listen for setup info from key player
	printf ("listening for network start info...\n");
	while (1)
	{
	    CheckAbort ();
	    if (!HGetPacket ())
		continue;
	    if (netbuffer->checksum & NCMD_SETUP)
	    {
		if (netbuffer->player != VERSION)
		    I_Error ("Different DOOM versions cannot play a net game!");
		startskill = netbuffer->retransmitfrom & 15;
		deathmatch = (netbuffer->retransmitfrom & 0xc0) >> 6;
		nomonsters = (netbuffer->retransmitfrom & 0x20) > 0;
		respawnparm = (netbuffer->retransmitfrom & 0x10) > 0;
		startmap = netbuffer->starttic & 0x3f;
		startepisode = netbuffer->starttic >> 6;
		return;
	    }
	}
    }
    else
    {
	// key player, send the setup info
	printf ("sending network start info...\n");
	do
	{
	    CheckAbort ();
	    for (i=0 ; i<doomcom->numnodes ; i++)
	    {
		netbuffer->retransmitfrom = startskill;
		if (deathmatch)
		    netbuffer->retransmitfrom |= (deathmatch<<6);
		if (nomonsters)
		    netbuffer->retransmitfrom |= 0x20;
		if (respawnparm)
		    netbuffer->retransmitfrom |= 0x10;
		netbuffer->starttic = startepisode * 64 + startmap;
		netbuffer->player = VERSION;
		netbuffer->numtics = 0;
		HSendPacket (i, NCMD_SETUP);
	    }

#if 1
	    for(i = 10 ; i  &&  HGetPacket(); --i)
	    {
		if((netbuffer->player&0x7f) < MAXNETNODES)
		    gotinfo[netbuffer->player&0x7f] = true;
	    }
#else
	    while (HGetPacket ())
	    {
		gotinfo[netbuffer->player&0x7f] = true;
	    }
#endif

	    for (i=1 ; i<doomcom->numnodes ; i++)
		if (!gotinfo[i])
		    break;
	} while (i < doomcom->numnodes);
    }
}