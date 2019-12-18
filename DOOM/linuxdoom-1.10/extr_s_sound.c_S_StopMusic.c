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
struct TYPE_2__ {scalar_t__ data; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_ResumeSong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I_StopSong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I_UnRegisterSong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PU_CACHE ; 
 int /*<<< orphan*/  Z_ChangeTag (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mus_paused ; 
 TYPE_1__* mus_playing ; 

void S_StopMusic(void)
{
    if (mus_playing)
    {
	if (mus_paused)
	    I_ResumeSong(mus_playing->handle);

	I_StopSong(mus_playing->handle);
	I_UnRegisterSong(mus_playing->handle);
	Z_ChangeTag(mus_playing->data, PU_CACHE);
	
	mus_playing->data = 0;
	mus_playing = 0;
    }
}