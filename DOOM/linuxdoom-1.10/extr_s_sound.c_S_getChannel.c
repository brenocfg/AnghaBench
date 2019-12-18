#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ priority; } ;
typedef  TYPE_1__ sfxinfo_t ;
struct TYPE_6__ {void* origin; TYPE_1__* sfxinfo; } ;
typedef  TYPE_2__ channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_StopChannel (int) ; 
 TYPE_2__* channels ; 
 int numChannels ; 

int
S_getChannel
( void*		origin,
  sfxinfo_t*	sfxinfo )
{
    // channel number to use
    int		cnum;
    
    channel_t*	c;

    // Find an open channel
    for (cnum=0 ; cnum<numChannels ; cnum++)
    {
	if (!channels[cnum].sfxinfo)
	    break;
	else if (origin &&  channels[cnum].origin ==  origin)
	{
	    S_StopChannel(cnum);
	    break;
	}
    }

    // None available
    if (cnum == numChannels)
    {
	// Look for lower priority
	for (cnum=0 ; cnum<numChannels ; cnum++)
	    if (channels[cnum].sfxinfo->priority >= sfxinfo->priority) break;

	if (cnum == numChannels)
	{
	    // FUCK!  No lower priority.  Sorry, Charlie.    
	    return -1;
	}
	else
	{
	    // Otherwise, kick out lower priority.
	    S_StopChannel(cnum);
	}
    }

    c = &channels[cnum];

    // channel is decided to be cnum.
    c->sfxinfo = sfxinfo;
    c->origin = origin;

    return cnum;
}