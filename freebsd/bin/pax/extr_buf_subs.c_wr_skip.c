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
typedef  long off_t ;

/* Variables and functions */
 int MIN (int,long) ; 
 int /*<<< orphan*/  blksz ; 
 int buf_flush (int /*<<< orphan*/ ) ; 
 int bufend ; 
 int bufpt ; 
 int /*<<< orphan*/  memset (int,int /*<<< orphan*/ ,int) ; 

int
wr_skip(off_t skcnt)
{
	int cnt;

	/*
	 * loop while there is more padding to add
	 */
	while (skcnt > 0L) {
		cnt = bufend - bufpt;
		if ((cnt <= 0) && ((cnt = buf_flush(blksz)) < 0))
			return(-1);
		cnt = MIN(cnt, skcnt);
		memset(bufpt, 0, cnt);
		bufpt += cnt;
		skcnt -= cnt;
	}
	return(0);
}