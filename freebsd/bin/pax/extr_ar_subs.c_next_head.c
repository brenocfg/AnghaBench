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
struct TYPE_2__ {int hsz; scalar_t__ (* rd ) (int /*<<< orphan*/ *,char*) ;int (* trail_tar ) (char*,int,int*) ;scalar_t__ (* trail_cpio ) (int /*<<< orphan*/ *) ;scalar_t__ inhead; } ;
typedef  int /*<<< orphan*/  ARCHD ;

/* Variables and functions */
 scalar_t__ APPND ; 
 scalar_t__ act ; 
 int /*<<< orphan*/  ar_drain () ; 
 int /*<<< orphan*/  flcnt ; 
 TYPE_1__* frmt ; 
 char* hdbuf ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 scalar_t__ rd_sync () ; 
 int rd_wrbuf (char*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,char*) ; 
 int stub2 (char*,int,int*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
next_head(ARCHD *arcn)
{
	int ret;
	char *hdend;
	int res;
	int shftsz;
	int hsz;
	int in_resync = 0; 	/* set when we are in resync mode */
	int cnt = 0;			/* counter for trailer function */
	int first = 1;			/* on 1st read, EOF isn't premature. */

	/*
	 * set up initial conditions, we want a whole frmt->hsz block as we
	 * have no data yet.
	 */
	res = hsz = frmt->hsz;
	hdend = hdbuf;
	shftsz = hsz - 1;
	for(;;) {
		/*
		 * keep looping until we get a contiguous FULL buffer
		 * (frmt->hsz is the proper size)
		 */
		for (;;) {
			if ((ret = rd_wrbuf(hdend, res)) == res)
				break;

			/*
			 * If we read 0 bytes (EOF) from an archive when we
			 * expect to find a header, we have stepped upon
			 * an archive without the customary block of zeroes
			 * end marker.  It's just stupid to error out on
			 * them, so exit gracefully.
			 */
			if (first && ret == 0)
				return(-1);
			first = 0;

			/*
			 * some kind of archive read problem, try to resync the
			 * storage device, better give the user the bad news.
			 */
			if ((ret == 0) || (rd_sync() < 0)) {
				paxwarn(1,"Premature end of file on archive read");
				return(-1);
			}
			if (!in_resync) {
				if (act == APPND) {
					paxwarn(1,
					  "Archive I/O error, cannot continue");
					return(-1);
				}
				paxwarn(1,"Archive I/O error. Trying to recover.");
				++in_resync;
			}

			/*
			 * oh well, throw it all out and start over
			 */
			res = hsz;
			hdend = hdbuf;
		}

		/*
		 * ok we have a contiguous buffer of the right size. Call the
		 * format read routine. If this was not a valid header and this
		 * format stores trailers outside of the header, call the
		 * format specific trailer routine to check for a trailer. We
		 * have to watch out that we do not mis-identify file data or
		 * block padding as a header or trailer. Format specific
		 * trailer functions must NOT check for the trailer while we
		 * are running in resync mode. Some trailer functions may tell
		 * us that this block cannot contain a valid header either, so
		 * we then throw out the entire block and start over.
		 */
		if ((*frmt->rd)(arcn, hdbuf) == 0)
			break;

		if (!frmt->inhead) {
			/*
			 * this format has trailers outside of valid headers
			 */
			if ((ret = (*frmt->trail_tar)(hdbuf,in_resync,&cnt)) == 0){
				/*
				 * valid trailer found, drain input as required
				 */
				ar_drain();
				return(-1);
			}

			if (ret == 1) {
				/*
				 * we are in resync and we were told to throw
				 * the whole block out because none of the
				 * bytes in this block can be used to form a
				 * valid header
				 */
				res = hsz;
				hdend = hdbuf;
				continue;
			}
		}

		/*
		 * Brute force section.
		 * not a valid header. We may be able to find a header yet. So
		 * we shift over by one byte, and set up to read one byte at a
		 * time from the archive and place it at the end of the buffer.
		 * We will keep moving byte at a time until we find a header or
		 * get a read error and have to start over.
		 */
		if (!in_resync) {
			if (act == APPND) {
				paxwarn(1,"Unable to append, archive header flaw");
				return(-1);
			}
			paxwarn(1,"Invalid header, starting valid header search.");
			++in_resync;
		}
		memmove(hdbuf, hdbuf+1, shftsz);
		res = 1;
		hdend = hdbuf + shftsz;
	}

	/*
	 * ok got a valid header, check for trailer if format encodes it in
	 * the header.
	 */
	if (frmt->inhead && ((*frmt->trail_cpio)(arcn) == 0)) {
		/*
		 * valid trailer found, drain input as required
		 */
		ar_drain();
		return(-1);
	}

	++flcnt;
	return(0);
}