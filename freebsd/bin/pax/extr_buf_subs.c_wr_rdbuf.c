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
 int MIN (int,int) ; 
 int /*<<< orphan*/  blksz ; 
 int buf_flush (int /*<<< orphan*/ ) ; 
 int bufend ; 
 int bufpt ; 
 int /*<<< orphan*/  memcpy (int,char*,int) ; 

int
wr_rdbuf(char *out, int outcnt)
{
	int cnt;

	/*
	 * while there is data to copy into the write buffer. when the
	 * write buffer fills, flush it to the archive and continue
	 */
	while (outcnt > 0) {
		cnt = bufend - bufpt;
		if ((cnt <= 0) && ((cnt = buf_flush(blksz)) < 0))
			return(-1);
		/*
		 * only move what we have space for
		 */
		cnt = MIN(cnt, outcnt);
		memcpy(bufpt, out, cnt);
		bufpt += cnt;
		out += cnt;
		outcnt -= cnt;
	}
	return(0);
}