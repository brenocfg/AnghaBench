#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int hsz; scalar_t__ (* id ) (char*,int) ;} ;

/* Variables and functions */
 scalar_t__ APPND ; 
 int BLKMULT ; 
 scalar_t__ act ; 
 size_t* ford ; 
 TYPE_1__* frmt ; 
 TYPE_1__* fsub ; 
 char* hdbuf ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 int /*<<< orphan*/  pback (char*,int) ; 
 scalar_t__ rd_start () ; 
 scalar_t__ rd_sync () ; 
 int rd_wrbuf (char*,int) ; 
 scalar_t__ stub1 (char*,int) ; 

__attribute__((used)) static int
get_arc(void)
{
	int i;
	int hdsz = 0;
	int res;
	int minhd = BLKMULT;
	char *hdend;
	int notice = 0;

	/*
	 * find the smallest header size in all archive formats and then set up
	 * to read the archive.
	 */
	for (i = 0; ford[i] >= 0; ++i) {
		if (fsub[ford[i]].hsz < minhd)
			minhd = fsub[ford[i]].hsz;
	}
	if (rd_start() < 0)
		return(-1);
	res = BLKMULT;
	hdsz = 0;
	hdend = hdbuf;
	for(;;) {
		for (;;) {
			/*
			 * fill the buffer with at least the smallest header
			 */
			i = rd_wrbuf(hdend, res);
			if (i > 0)
				hdsz += i;
			if (hdsz >= minhd)
				break;

			/*
			 * if we cannot recover from a read error quit
			 */
			if ((i == 0) || (rd_sync() < 0))
				goto out;

			/*
			 * when we get an error none of the data we already
			 * have can be used to create a legal header (we just
			 * got an error in the middle), so we throw it all out
			 * and refill the buffer with fresh data.
			 */
			res = BLKMULT;
			hdsz = 0;
			hdend = hdbuf;
			if (!notice) {
				if (act == APPND)
					return(-1);
				paxwarn(1,"Cannot identify format. Searching...");
				++notice;
			}
		}

		/*
		 * we have at least the size of the smallest header in any
		 * archive format. Look to see if we have a match. The array
		 * ford[] is used to specify the header id order to reduce the
		 * chance of incorrectly id'ing a valid header (some formats
		 * may be subsets of each other and the order would then be
		 * important).
		 */
		for (i = 0; ford[i] >= 0; ++i) {
			if ((*fsub[ford[i]].id)(hdbuf, hdsz) < 0)
				continue;
			frmt = &(fsub[ford[i]]);
			/*
			 * yuck, to avoid slow special case code in the extract
			 * routines, just push this header back as if it was
			 * not seen. We have left extra space at start of the
			 * buffer for this purpose. This is a bit ugly, but
			 * adding all the special case code is far worse.
			 */
			pback(hdbuf, hdsz);
			return(0);
		}

		/*
		 * We have a flawed archive, no match. we start searching, but
		 * we never allow additions to flawed archives
		 */
		if (!notice) {
			if (act == APPND)
				return(-1);
			paxwarn(1, "Cannot identify format. Searching...");
			++notice;
		}

		/*
		 * brute force search for a header that we can id.
		 * we shift through byte at a time. this is slow, but we cannot
		 * determine the nature of the flaw in the archive in a
		 * portable manner
		 */
		if (--hdsz > 0) {
			memmove(hdbuf, hdbuf+1, hdsz);
			res = BLKMULT - hdsz;
			hdend = hdbuf + hdsz;
		} else {
			res = BLKMULT;
			hdend = hdbuf;
			hdsz = 0;
		}
	}

    out:
	/*
	 * we cannot find a header, bow, apologize and quit
	 */
	paxwarn(1, "Sorry, unable to determine archive format.");
	return(-1);
}