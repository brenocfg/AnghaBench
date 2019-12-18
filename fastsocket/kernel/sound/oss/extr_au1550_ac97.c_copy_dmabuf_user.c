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
struct dmabuf {char* nextOut; char* nextIn; char* rawbuf; int dmasize; } ;

/* Variables and functions */
 int translate_from_user (struct dmabuf*,char*,char*,int) ; 
 int translate_to_user (struct dmabuf*,char*,char*,int) ; 

__attribute__((used)) static int
copy_dmabuf_user(struct dmabuf *db, char* userbuf, int count, int to_user)
{
	char           *bufptr = to_user ? db->nextOut : db->nextIn;
	char           *bufend = db->rawbuf + db->dmasize;
	int             cnt, ret;

	if (bufptr + count > bufend) {
		int             partial = (int) (bufend - bufptr);
		if (to_user) {
			if ((cnt = translate_to_user(db, userbuf,
						     bufptr, partial)) < 0)
				return cnt;
			ret = cnt;
			if ((cnt = translate_to_user(db, userbuf + partial,
						     db->rawbuf,
						     count - partial)) < 0)
				return cnt;
			ret += cnt;
		} else {
			if ((cnt = translate_from_user(db, bufptr, userbuf,
						       partial)) < 0)
				return cnt;
			ret = cnt;
			if ((cnt = translate_from_user(db, db->rawbuf,
						       userbuf + partial,
						       count - partial)) < 0)
				return cnt;
			ret += cnt;
		}
	} else {
		if (to_user)
			ret = translate_to_user(db, userbuf, bufptr, count);
		else
			ret = translate_from_user(db, bufptr, userbuf, count);
	}

	return ret;
}