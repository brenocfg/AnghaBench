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
 scalar_t__ ar_next () ; 
 int ar_read (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blksz ; 
 void* buf ; 
 void* bufend ; 
 void* bufpt ; 
 int exit_val ; 
 int /*<<< orphan*/ * frmt ; 
 scalar_t__ rdcnt ; 

int
buf_fill(void)
{
	int cnt;
	static int fini = 0;

	if (fini)
		return(0);

	for(;;) {
		/*
		 * try to fill the buffer. on error the next archive volume is
		 * opened and we try again.
		 */
		if ((cnt = ar_read(buf, blksz)) > 0) {
			bufpt = buf;
			bufend = buf + cnt;
			rdcnt += cnt;
			return(cnt);
		}

		/*
		 * errors require resync, EOF goes to next archive
		 * but in case we have not determined yet the format,
		 * this means that we have a very short file, so we
		 * are done again.
		 */
		if (cnt < 0)
			break;
		if (frmt == NULL || ar_next() < 0) {
			fini = 1;
			return(0);
		}
		rdcnt = 0;
	}
	exit_val = 1;
	return(-1);
}