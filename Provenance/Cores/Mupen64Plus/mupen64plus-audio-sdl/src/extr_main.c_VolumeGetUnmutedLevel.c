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
 scalar_t__ VOLUME_TYPE_OSS ; 
 int /*<<< orphan*/  VolIsMuted ; 
 int VolPercent ; 
 scalar_t__ VolumeControlType ; 
 int volGet () ; 

__attribute__((used)) static int VolumeGetUnmutedLevel(void)
{
#if defined(HAS_OSS_SUPPORT)
    // reload volume if we're using OSS
    if (!VolIsMuted && VolumeControlType == VOLUME_TYPE_OSS)
    {
        return volGet();
    }
#endif

    return VolPercent;
}