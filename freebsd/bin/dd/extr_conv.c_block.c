#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_6__ {char* db; size_t dbrcnt; size_t dbcnt; char* dbp; } ;
struct TYPE_5__ {char* dbp; size_t dbcnt; size_t dbsz; } ;
struct TYPE_4__ {int /*<<< orphan*/  trunc; } ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 size_t cbsz ; 
 char* ctab ; 
 int /*<<< orphan*/  dd_out (int /*<<< orphan*/ ) ; 
 TYPE_3__ in ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 TYPE_2__ out ; 
 TYPE_1__ st ; 

void
block(void)
{
	u_char *inp, *outp;
	const u_char *t;
	size_t cnt, maxlen;
	static int intrunc;
	int ch;

	/*
	 * Record truncation can cross block boundaries.  If currently in a
	 * truncation state, keep tossing characters until reach a newline.
	 * Start at the beginning of the buffer, as the input buffer is always
	 * left empty.
	 */
	if (intrunc) {
		for (inp = in.db, cnt = in.dbrcnt; cnt && *inp++ != '\n'; --cnt)
			;
		if (!cnt) {
			in.dbcnt = 0;
			in.dbp = in.db;
			return;
		}
		intrunc = 0;
		/* Adjust the input buffer numbers. */
		in.dbcnt = cnt - 1;
		in.dbp = inp + cnt - 1;
	}

	/*
	 * Copy records (max cbsz size chunks) into the output buffer.  The
	 * translation is done as we copy into the output buffer.
	 */
	ch = 0;
	for (inp = in.dbp - in.dbcnt, outp = out.dbp; in.dbcnt;) {
		maxlen = MIN(cbsz, (size_t)in.dbcnt);
		if ((t = ctab) != NULL)
			for (cnt = 0; cnt < maxlen && (ch = *inp++) != '\n';
			    ++cnt)
				*outp++ = t[ch];
		else
			for (cnt = 0; cnt < maxlen && (ch = *inp++) != '\n';
			    ++cnt)
				*outp++ = ch;
		/*
		 * Check for short record without a newline.  Reassemble the
		 * input block.
		 */
		if (ch != '\n' && (size_t)in.dbcnt < cbsz) {
			(void)memmove(in.db, in.dbp - in.dbcnt, in.dbcnt);
			break;
		}

		/* Adjust the input buffer numbers. */
		in.dbcnt -= cnt;
		if (ch == '\n')
			--in.dbcnt;

		/* Pad short records with spaces. */
		if (cnt < cbsz)
			(void)memset(outp, ctab ? ctab[' '] : ' ', cbsz - cnt);
		else {
			/*
			 * If the next character wouldn't have ended the
			 * block, it's a truncation.
			 */
			if (!in.dbcnt || *inp != '\n')
				++st.trunc;

			/* Toss characters to a newline. */
			for (; in.dbcnt && *inp++ != '\n'; --in.dbcnt)
				;
			if (!in.dbcnt)
				intrunc = 1;
			else
				--in.dbcnt;
		}

		/* Adjust output buffer numbers. */
		out.dbp += cbsz;
		if ((out.dbcnt += cbsz) >= out.dbsz)
			dd_out(0);
		outp = out.dbp;
	}
	in.dbp = in.db + in.dbcnt;
}