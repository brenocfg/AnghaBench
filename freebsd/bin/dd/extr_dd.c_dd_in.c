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
typedef  scalar_t__ uintmax_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_6__ {int dbsz; int dbrcnt; int flags; scalar_t__ dbp; scalar_t__ dbcnt; int /*<<< orphan*/  name; int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {scalar_t__ dbcnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  swab; scalar_t__ in_part; scalar_t__ in_full; } ;

/* Variables and functions */
 int C_BLOCK ; 
 int C_BS ; 
 int C_FILL ; 
 int C_IFULLBLOCK ; 
 int C_NOERROR ; 
 int C_NOTRUNC ; 
 int C_SWAB ; 
 int C_SYNC ; 
 int C_UNBLOCK ; 
 int ISSEEK ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  cfunc () ; 
 int cpy_cnt ; 
 int /*<<< orphan*/  dd_out (int) ; 
 int ddflags ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 char fill_char ; 
 TYPE_3__ in ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,char,int) ; 
 scalar_t__ need_progress ; 
 scalar_t__ need_summary ; 
 TYPE_2__ out ; 
 int /*<<< orphan*/  progress () ; 
 int read (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ speed ; 
 int /*<<< orphan*/  speed_limit () ; 
 TYPE_1__ st ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  summary () ; 
 int /*<<< orphan*/  swapbytes (scalar_t__,size_t) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dd_in(void)
{
	ssize_t n;

	for (;;) {
		switch (cpy_cnt) {
		case -1:			/* count=0 was specified */
			return;
		case 0:
			break;
		default:
			if (st.in_full + st.in_part >= (uintmax_t)cpy_cnt)
				return;
			break;
		}

		if (speed > 0)
			speed_limit();

		/*
		 * Zero the buffer first if sync; if doing block operations,
		 * use spaces.
		 */
		if (ddflags & C_SYNC) {
			if (ddflags & C_FILL)
				memset(in.dbp, fill_char, in.dbsz);
			else if (ddflags & (C_BLOCK | C_UNBLOCK))
				memset(in.dbp, ' ', in.dbsz);
			else
				memset(in.dbp, 0, in.dbsz);
		}

		in.dbrcnt = 0;
fill:
		n = read(in.fd, in.dbp + in.dbrcnt, in.dbsz - in.dbrcnt);

		/* EOF */
		if (n == 0 && in.dbrcnt == 0)
			return;

		/* Read error */
		if (n == -1) {
			/*
			 * If noerror not specified, die.  POSIX requires that
			 * the warning message be followed by an I/O display.
			 */
			if (!(ddflags & C_NOERROR))
				err(1, "%s", in.name);
			warn("%s", in.name);
			summary();

			/*
			 * If it's a seekable file descriptor, seek past the
			 * error.  If your OS doesn't do the right thing for
			 * raw disks this section should be modified to re-read
			 * in sector size chunks.
			 */
			if (in.flags & ISSEEK &&
			    lseek(in.fd, (off_t)in.dbsz, SEEK_CUR))
				warn("%s", in.name);

			/* If sync not specified, omit block and continue. */
			if (!(ddflags & C_SYNC))
				continue;
		}

		/* If conv=sync, use the entire block. */
		if (ddflags & C_SYNC)
			n = in.dbsz;

		/* Count the bytes read for this block. */
		in.dbrcnt += n;

		/* Count the number of full and partial blocks. */
		if (in.dbrcnt == in.dbsz)
			++st.in_full;
		else if (ddflags & C_IFULLBLOCK && n != 0)
			goto fill; /* these don't count */
		else
			++st.in_part;

		/* Count the total bytes read for this file. */
		in.dbcnt += in.dbrcnt;

		/*
		 * POSIX states that if bs is set and no other conversions
		 * than noerror, notrunc or sync are specified, the block
		 * is output without buffering as it is read.
		 */
		if ((ddflags & ~(C_NOERROR | C_NOTRUNC | C_SYNC)) == C_BS) {
			out.dbcnt = in.dbcnt;
			dd_out(1);
			in.dbcnt = 0;
			continue;
		}

		if (ddflags & C_SWAB) {
			if ((n = in.dbrcnt) & 1) {
				++st.swab;
				--n;
			}
			swapbytes(in.dbp, (size_t)n);
		}

		/* Advance to the next block. */
		in.dbp += in.dbrcnt;
		(*cfunc)();
		if (need_summary)
			summary();
		if (need_progress)
			progress();
	}
}