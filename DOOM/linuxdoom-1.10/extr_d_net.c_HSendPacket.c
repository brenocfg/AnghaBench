#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int byte ;
struct TYPE_5__ {int remotenode; int datalength; int /*<<< orphan*/  command; } ;
struct TYPE_4__ {int checksum; int numtics; int /*<<< orphan*/  starttic; int /*<<< orphan*/  retransmitfrom; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SEND ; 
 int ExpandTics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I_Error (char*) ; 
 int /*<<< orphan*/  I_NetCmd () ; 
 int NCMD_RETRANSMIT ; 
 int NetbufferChecksum () ; 
 int NetbufferSize () ; 
 scalar_t__ debugfile ; 
 scalar_t__ demoplayback ; 
 TYPE_3__* doomcom ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 TYPE_1__* netbuffer ; 
 int /*<<< orphan*/  netgame ; 
 int reboundpacket ; 
 TYPE_1__ reboundstore ; 

void
HSendPacket
 (int	node,
  int	flags )
{
    netbuffer->checksum = NetbufferChecksum () | flags;

    if (!node)
    {
	reboundstore = *netbuffer;
	reboundpacket = true;
	return;
    }

    if (demoplayback)
	return;

    if (!netgame)
	I_Error ("Tried to transmit to another node");
		
    doomcom->command = CMD_SEND;
    doomcom->remotenode = node;
    doomcom->datalength = NetbufferSize ();
	
    if (debugfile)
    {
	int		i;
	int		realretrans;
	if (netbuffer->checksum & NCMD_RETRANSMIT)
	    realretrans = ExpandTics (netbuffer->retransmitfrom);
	else
	    realretrans = -1;

	fprintf (debugfile,"send (%i + %i, R %i) [%i] ",
		 ExpandTics(netbuffer->starttic),
		 netbuffer->numtics, realretrans, doomcom->datalength);
	
	for (i=0 ; i<doomcom->datalength ; i++)
	    fprintf (debugfile,"%i ",((byte *)netbuffer)[i]);

	fprintf (debugfile,"\n");
    }

    I_NetCmd ();
}