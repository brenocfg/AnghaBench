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
 int /*<<< orphan*/  GZBUFSIZE ; 
 int /*<<< orphan*/  gzbuf ; 
 int /*<<< orphan*/  gzgets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playbackfp ; 
 scalar_t__ playingback ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int*) ; 

int INPUT_PlaybackInt(void)
{
#ifdef EVENT_RECORDING
	int i;
	if (playingback) {
		gzgets(playbackfp, gzbuf, GZBUFSIZE);
		sscanf(gzbuf, "%d", &i);
	}
	return i;
#else
	return 0;
#endif
}