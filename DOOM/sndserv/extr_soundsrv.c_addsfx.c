#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 TYPE_1__* S_sfx ; 
 int* channelhandles ; 
 int* channelids ; 
 int /*<<< orphan*/ ** channelleftvol_lookup ; 
 int /*<<< orphan*/ ** channelrightvol_lookup ; 
 unsigned char** channels ; 
 unsigned char** channelsend ; 
 int* channelstart ; 
 int* channelstep ; 
 scalar_t__* channelstepremainder ; 
 int /*<<< orphan*/  derror (char*) ; 
 int* lengths ; 
 int mytime ; 
 int sfx_pistol ; 
 int sfx_sawful ; 
 int sfx_sawhit ; 
 int sfx_sawidl ; 
 int sfx_sawup ; 
 int sfx_stnmov ; 
 int /*<<< orphan*/ * vol_lookup ; 

int
addsfx
( int		sfxid,
  int		volume,
  int		step,
  int		seperation )
{
    static unsigned short	handlenums = 0;
 
    int		i;
    int		rc = -1;
    
    int		oldest = mytime;
    int		oldestnum = 0;
    int		slot;
    int		rightvol;
    int		leftvol;

    // play these sound effects
    //  only one at a time
    if ( sfxid == sfx_sawup
	 || sfxid == sfx_sawidl
	 || sfxid == sfx_sawful
	 || sfxid == sfx_sawhit
	 || sfxid == sfx_stnmov
	 || sfxid == sfx_pistol )
    {
	for (i=0 ; i<8 ; i++)
	{
	    if (channels[i] && channelids[i] == sfxid)
	    {
		channels[i] = 0;
		break;
	    }
	}
    }

    for (i=0 ; i<8 && channels[i] ; i++)
    {
	if (channelstart[i] < oldest)
	{
	    oldestnum = i;
	    oldest = channelstart[i];
	}
    }

    if (i == 8)
	slot = oldestnum;
    else
	slot = i;

    channels[slot] = (unsigned char *) S_sfx[sfxid].data;
    channelsend[slot] = channels[slot] + lengths[sfxid];

    if (!handlenums)
	handlenums = 100;
    
    channelhandles[slot] = rc = handlenums++;
    channelstep[slot] = step;
    channelstepremainder[slot] = 0;
    channelstart[slot] = mytime;

    // (range: 1 - 256)
    seperation += 1;

    // (x^2 seperation)
    leftvol =
	volume - (volume*seperation*seperation)/(256*256);

    seperation = seperation - 257;

    // (x^2 seperation)
    rightvol =
	volume - (volume*seperation*seperation)/(256*256);	

    // sanity check
    if (rightvol < 0 || rightvol > 127)
	derror("rightvol out of bounds");
    
    if (leftvol < 0 || leftvol > 127)
	derror("leftvol out of bounds");
    
    // get the proper lookup table piece
    //  for this volume level
    channelleftvol_lookup[slot] = &vol_lookup[leftvol*256];
    channelrightvol_lookup[slot] = &vol_lookup[rightvol*256];

    channelids[slot] = sfxid;

    return rc;

}