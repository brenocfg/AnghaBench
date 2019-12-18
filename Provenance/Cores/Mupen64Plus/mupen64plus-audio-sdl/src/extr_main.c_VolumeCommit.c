#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int SDL_MIX_MAXVOLUME ; 
 scalar_t__ VOLUME_TYPE_OSS ; 
 scalar_t__ VolIsMuted ; 
 int VolPercent ; 
 int VolSDL ; 
 scalar_t__ VolumeControlType ; 
 int /*<<< orphan*/  volSet (int) ; 

__attribute__((used)) static void VolumeCommit(void)
{
    int levelToCommit = VolIsMuted ? 0 : VolPercent;

#if defined(HAS_OSS_SUPPORT)
    if (VolumeControlType == VOLUME_TYPE_OSS)
    {
        //OSS mixer volume
        volSet(levelToCommit);
    }
    else
#endif
    {
        VolSDL = SDL_MIX_MAXVOLUME * levelToCommit / 100;
    }
}