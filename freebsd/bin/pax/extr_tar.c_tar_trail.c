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
 int BLKMULT ; 
 int NULLCNT ; 

int
tar_trail(char *buf, int in_resync, int *cnt)
{
	int i;

	/*
	 * look for all zero, trailer is two consecutive blocks of zero
	 */
	for (i = 0; i < BLKMULT; ++i) {
		if (buf[i] != '\0')
			break;
	}

	/*
	 * if not all zero it is not a trailer, but MIGHT be a header.
	 */
	if (i != BLKMULT)
		return(-1);

	/*
	 * When given a zero block, we must be careful!
	 * If we are not in resync mode, check for the trailer. Have to watch
	 * out that we do not mis-identify file data as the trailer, so we do
	 * NOT try to id a trailer during resync mode. During resync mode we
	 * might as well throw this block out since a valid header can NEVER be
	 * a block of all 0 (we must have a valid file name).
	 */
	if (!in_resync && (++*cnt >= NULLCNT))
		return(0);
	return(1);
}