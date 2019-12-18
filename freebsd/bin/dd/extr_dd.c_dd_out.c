#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ssize_t ;
struct TYPE_4__ {size_t dbcnt; size_t dbsz; int seek_offset; int flags; int /*<<< orphan*/ * db; int /*<<< orphan*/ * dbp; int /*<<< orphan*/  name; int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {size_t bytes; int /*<<< orphan*/  out_part; int /*<<< orphan*/  out_full; } ;

/* Variables and functions */
 int BISZERO (int /*<<< orphan*/ *,size_t) ; 
 int C_SPARSE ; 
 scalar_t__ EINTR ; 
 int ISCHR ; 
 int ISTAPE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int ddflags ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 TYPE_2__ out ; 
 scalar_t__ pending ; 
 TYPE_1__ st ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 
 size_t write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

void
dd_out(int force)
{
	u_char *outp;
	size_t cnt, n;
	ssize_t nw;
	static int warned;
	int sparse;

	/*
	 * Write one or more blocks out.  The common case is writing a full
	 * output block in a single write; increment the full block stats.
	 * Otherwise, we're into partial block writes.  If a partial write,
	 * and it's a character device, just warn.  If a tape device, quit.
	 *
	 * The partial writes represent two cases.  1: Where the input block
	 * was less than expected so the output block was less than expected.
	 * 2: Where the input block was the right size but we were forced to
	 * write the block in multiple chunks.  The original versions of dd(1)
	 * never wrote a block in more than a single write, so the latter case
	 * never happened.
	 *
	 * One special case is if we're forced to do the write -- in that case
	 * we play games with the buffer size, and it's usually a partial write.
	 */
	outp = out.db;

	/*
	 * If force, first try to write all pending data, else try to write
	 * just one block. Subsequently always write data one full block at
	 * a time at most.
	 */
	for (n = force ? out.dbcnt : out.dbsz;; n = out.dbsz) {
		cnt = n;
		do {
			sparse = 0;
			if (ddflags & C_SPARSE) {
				/* Is buffer sparse? */
				sparse = BISZERO(outp, cnt);
			}
			if (sparse && !force) {
				pending += cnt;
				nw = cnt;
			} else {
				if (pending != 0) {
					/*
					 * Seek past hole.  Note that we need to record the
					 * reached offset, because we might have no more data
					 * to write, in which case we'll need to call
					 * ftruncate to extend the file size.
					 */
					out.seek_offset = lseek(out.fd, pending, SEEK_CUR);
					if (out.seek_offset == -1)
						err(2, "%s: seek error creating sparse file",
						    out.name);
					pending = 0;
				}
				if (cnt) {
					nw = write(out.fd, outp, cnt);
					out.seek_offset = 0;
				} else {
					return;
				}
			}

			if (nw <= 0) {
				if (nw == 0)
					errx(1, "%s: end of device", out.name);
				if (errno != EINTR)
					err(1, "%s", out.name);
				nw = 0;
			}

			outp += nw;
			st.bytes += nw;

			if ((size_t)nw == n && n == (size_t)out.dbsz)
				++st.out_full;
			else
				++st.out_part;

			if ((size_t) nw != cnt) {
				if (out.flags & ISTAPE)
					errx(1, "%s: short write on tape device",
				    	out.name);
				if (out.flags & ISCHR && !warned) {
					warned = 1;
					warnx("%s: short write on character device",
				    	out.name);
				}
			}

			cnt -= nw;
		} while (cnt != 0);

		if ((out.dbcnt -= n) < out.dbsz)
			break;
	}

	/* Reassemble the output block. */
	if (out.dbcnt)
		(void)memmove(out.db, out.dbp - out.dbcnt, out.dbcnt);
	out.dbp = out.db + out.dbcnt;
}