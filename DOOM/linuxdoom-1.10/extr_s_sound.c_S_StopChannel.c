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
struct TYPE_4__ {TYPE_3__* sfxinfo; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ channel_t ;
struct TYPE_5__ {int /*<<< orphan*/  usefulness; } ;

/* Variables and functions */
 scalar_t__ I_SoundIsPlaying (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I_StopSound (int /*<<< orphan*/ ) ; 
 TYPE_3__* S_sfx ; 
 TYPE_1__* channels ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int numChannels ; 
 size_t sfx_sawful ; 
 int /*<<< orphan*/  stderr ; 

void S_StopChannel(int cnum)
{

    int		i;
    channel_t*	c = &channels[cnum];

    if (c->sfxinfo)
    {
	// stop the sound playing
	if (I_SoundIsPlaying(c->handle))
	{
#ifdef SAWDEBUG
	    if (c->sfxinfo == &S_sfx[sfx_sawful])
		fprintf(stderr, "stopped\n");
#endif
	    I_StopSound(c->handle);
	}

	// check to see
	//  if other channels are playing the sound
	for (i=0 ; i<numChannels ; i++)
	{
	    if (cnum != i
		&& c->sfxinfo == channels[i].sfxinfo)
	    {
		break;
	    }
	}
	
	// degrade usefulness of sound data
	c->sfxinfo->usefulness--;

	c->sfxinfo = 0;
    }
}