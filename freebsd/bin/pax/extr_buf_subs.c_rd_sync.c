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
 scalar_t__ APPND ; 
 scalar_t__ act ; 
 scalar_t__ ar_next () ; 
 scalar_t__ ar_rdsync () ; 
 int ar_read (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blksz ; 
 void* buf ; 
 void* bufend ; 
 void* bufpt ; 
 int maxflt ; 
 int /*<<< orphan*/  paxwarn (int,char*,...) ; 
 scalar_t__ rdcnt ; 

int
rd_sync(void)
{
	int errcnt = 0;
	int res;

	/*
	 * if the user says bail out on first fault, we are out of here...
	 */
	if (maxflt == 0)
		return(-1);
	if (act == APPND) {
		paxwarn(1, "Unable to append when there are archive read errors.");
		return(-1);
	}

	/*
	 * poke at device and try to get past media error
	 */
	if (ar_rdsync() < 0) {
		if (ar_next() < 0)
			return(-1);
		else
			rdcnt = 0;
	}

	for (;;) {
		if ((res = ar_read(buf, blksz)) > 0) {
			/*
			 * All right! got some data, fill that buffer
			 */
			bufpt = buf;
			bufend = buf + res;
			rdcnt += res;
			return(0);
		}

		/*
		 * Oh well, yet another failed read...
		 * if error limit reached, ditch. o.w. poke device to move past
		 * bad media and try again. if media is badly damaged, we ask
		 * the poor (and upset user at this point) for the next archive
		 * volume. remember the goal on reads is to get the most we
		 * can extract out of the archive.
		 */
		if ((maxflt > 0) && (++errcnt > maxflt))
			paxwarn(0,"Archive read error limit (%d) reached",maxflt);
		else if (ar_rdsync() == 0)
			continue;
		if (ar_next() < 0)
			break;
		rdcnt = 0;
		errcnt = 0;
	}
	return(-1);
}