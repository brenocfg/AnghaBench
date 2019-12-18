#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int pitch; scalar_t__ volume; scalar_t__ link; } ;
typedef  TYPE_1__ sfxinfo_t ;
typedef  int /*<<< orphan*/  mobj_t ;
struct TYPE_5__ {void* origin; int /*<<< orphan*/  handle; TYPE_1__* sfxinfo; } ;
typedef  TYPE_2__ channel_t ;

/* Variables and functions */
 scalar_t__ I_SoundIsPlaying (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I_UpdateSoundParams (int /*<<< orphan*/ ,int,int,int) ; 
 int NORM_PITCH ; 
 int NORM_SEP ; 
 int S_AdjustSoundParams (int /*<<< orphan*/ *,void*,int*,int*,int*) ; 
 int /*<<< orphan*/  S_StopChannel (int) ; 
 TYPE_2__* channels ; 
 int numChannels ; 
 int snd_SfxVolume ; 

void S_UpdateSounds(void* listener_p)
{
    int		audible;
    int		cnum;
    int		volume;
    int		sep;
    int		pitch;
    sfxinfo_t*	sfx;
    channel_t*	c;
    
    mobj_t*	listener = (mobj_t*)listener_p;


    
    // Clean up unused data.
    // This is currently not done for 16bit (sounds cached static).
    // DOS 8bit remains. 
    /*if (gametic > nextcleanup)
    {
	for (i=1 ; i<NUMSFX ; i++)
	{
	    if (S_sfx[i].usefulness < 1
		&& S_sfx[i].usefulness > -1)
	    {
		if (--S_sfx[i].usefulness == -1)
		{
		    Z_ChangeTag(S_sfx[i].data, PU_CACHE);
		    S_sfx[i].data = 0;
		}
	    }
	}
	nextcleanup = gametic + 15;
    }*/
    
    for (cnum=0 ; cnum<numChannels ; cnum++)
    {
	c = &channels[cnum];
	sfx = c->sfxinfo;

	if (c->sfxinfo)
	{
	    if (I_SoundIsPlaying(c->handle))
	    {
		// initialize parameters
		volume = snd_SfxVolume;
		pitch = NORM_PITCH;
		sep = NORM_SEP;

		if (sfx->link)
		{
		    pitch = sfx->pitch;
		    volume += sfx->volume;
		    if (volume < 1)
		    {
			S_StopChannel(cnum);
			continue;
		    }
		    else if (volume > snd_SfxVolume)
		    {
			volume = snd_SfxVolume;
		    }
		}

		// check non-local sounds for distance clipping
		//  or modify their params
		if (c->origin && listener_p != c->origin)
		{
		    audible = S_AdjustSoundParams(listener,
						  c->origin,
						  &volume,
						  &sep,
						  &pitch);
		    
		    if (!audible)
		    {
			S_StopChannel(cnum);
		    }
		    else
			I_UpdateSoundParams(c->handle, volume, sep, pitch);
		}
	    }
	    else
	    {
		// if channel is allocated but sound has stopped,
		//  free it
		S_StopChannel(cnum);
	    }
	}
    }
    // kill music if it is a single-play && finished
    // if (	mus_playing
    //      && !I_QrySongPlaying(mus_playing->handle)
    //      && !mus_paused )
    // S_StopMusic();
}