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
struct mtop {int mt_count; int /*<<< orphan*/  mt_op; } ;
typedef  int ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_3__ {int flags; char* name; scalar_t__ offset; int dbsz; int /*<<< orphan*/  db; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int ISPIPE ; 
 int ISSEEK ; 
 int /*<<< orphan*/  MTBSR ; 
 int /*<<< orphan*/  MTFSR ; 
 int /*<<< orphan*/  MTIOCTOP ; 
 int NOREAD ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtop*) ; 
 int lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ out ; 
 int read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seek_offset (TYPE_1__*) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
pos_out(void)
{
	struct mtop t_op;
	off_t cnt;
	ssize_t n;

	/*
	 * If not a tape, try seeking on the file.  Seeking on a pipe is
	 * going to fail, but don't protect the user -- they shouldn't
	 * have specified the seek operand.
	 */
	if (out.flags & (ISSEEK | ISPIPE)) {
		errno = 0;
		if (lseek(out.fd, seek_offset(&out), SEEK_CUR) == -1 &&
		    errno != 0)
			err(1, "%s", out.name);
		return;
	}

	/* Don't try to read a really weird amount (like negative). */
	if (out.offset < 0)
		errx(1, "%s: illegal offset", "oseek/seek");

	/* If no read access, try using mtio. */
	if (out.flags & NOREAD) {
		t_op.mt_op = MTFSR;
		t_op.mt_count = out.offset;

		if (ioctl(out.fd, MTIOCTOP, &t_op) == -1)
			err(1, "%s", out.name);
		return;
	}

	/* Read it. */
	for (cnt = 0; cnt < out.offset; ++cnt) {
		if ((n = read(out.fd, out.db, out.dbsz)) > 0)
			continue;

		if (n == -1)
			err(1, "%s", out.name);

		/*
		 * If reach EOF, fill with NUL characters; first, back up over
		 * the EOF mark.  Note, cnt has not yet been incremented, so
		 * the EOF read does not count as a seek'd block.
		 */
		t_op.mt_op = MTBSR;
		t_op.mt_count = 1;
		if (ioctl(out.fd, MTIOCTOP, &t_op) == -1)
			err(1, "%s", out.name);

		while (cnt++ < out.offset) {
			n = write(out.fd, out.db, out.dbsz);
			if (n == -1)
				err(1, "%s", out.name);
			if (n != out.dbsz)
				errx(1, "%s: write failure", out.name);
		}
		break;
	}
}