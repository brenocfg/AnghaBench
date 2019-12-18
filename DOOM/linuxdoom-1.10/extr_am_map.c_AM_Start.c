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
 int /*<<< orphan*/  AM_LevelInit () ; 
 int /*<<< orphan*/  AM_Stop () ; 
 int /*<<< orphan*/  AM_initVariables () ; 
 int /*<<< orphan*/  AM_loadPics () ; 
 int gameepisode ; 
 int gamemap ; 
 int stopped ; 

void AM_Start (void)
{
    static int lastlevel = -1, lastepisode = -1;

    if (!stopped) AM_Stop();
    stopped = false;
    if (lastlevel != gamemap || lastepisode != gameepisode)
    {
	AM_LevelInit();
	lastlevel = gamemap;
	lastepisode = gameepisode;
    }
    AM_initVariables();
    AM_loadPics();
}