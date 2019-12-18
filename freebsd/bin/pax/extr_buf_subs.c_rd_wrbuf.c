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
 int buf_fill () ; 
 int bufend ; 
 int bufpt ; 
 int /*<<< orphan*/  memcpy (char*,int,int) ; 

int
rd_wrbuf(char *in, int cpcnt)
{
	int res;
	int cnt;
	int incnt = cpcnt;

	/*
	 * loop until we fill the buffer with the requested number of bytes
	 */
	while (incnt > 0) {
		cnt = bufend - bufpt;
		if ((cnt <= 0) && ((cnt = buf_fill()) <= 0)) {
			/*
			 * read error, return what we got (or the error if
			 * no data was copied). The caller must know that an
			 * error occurred and has the best knowledge what to
			 * do with it
			 */
			if ((res = cpcnt - incnt) > 0)
				return(res);
			return(cnt);
		}

		/*
		 * calculate how much data to copy based on whats left and
		 * state of buffer
		 */
		cnt = MIN(cnt, incnt);
		memcpy(in, bufpt, cnt);
		bufpt += cnt;
		incnt -= cnt;
		in += cnt;
	}
	return(cpcnt);
}