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
struct TYPE_2__ {scalar_t__ dbcnt; scalar_t__ dbsz; scalar_t__ seek_offset; int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  fd; int /*<<< orphan*/  dbp; } ;

/* Variables and functions */
 int C_BLOCK ; 
 int C_FDATASYNC ; 
 int C_FILL ; 
 int C_FSYNC ; 
 int C_OSYNC ; 
 int C_UNBLOCK ; 
 int ISTRUNC ; 
 scalar_t__ block ; 
 int /*<<< orphan*/  block_close () ; 
 scalar_t__ cfunc ; 
 int /*<<< orphan*/  dd_out (int) ; 
 int ddflags ; 
 scalar_t__ def ; 
 int /*<<< orphan*/  def_close () ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int fdatasync (int /*<<< orphan*/ ) ; 
 char fill_char ; 
 int fsync (int /*<<< orphan*/ ) ; 
 int ftruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,scalar_t__) ; 
 TYPE_1__ out ; 
 scalar_t__ pending ; 
 scalar_t__ unblock ; 
 int /*<<< orphan*/  unblock_close () ; 

__attribute__((used)) static void
dd_close(void)
{
	if (cfunc == def)
		def_close();
	else if (cfunc == block)
		block_close();
	else if (cfunc == unblock)
		unblock_close();
	if (ddflags & C_OSYNC && out.dbcnt && out.dbcnt < out.dbsz) {
		if (ddflags & C_FILL)
			memset(out.dbp, fill_char, out.dbsz - out.dbcnt);
		else if (ddflags & (C_BLOCK | C_UNBLOCK))
			memset(out.dbp, ' ', out.dbsz - out.dbcnt);
		else
			memset(out.dbp, 0, out.dbsz - out.dbcnt);
		out.dbcnt = out.dbsz;
	}
	if (out.dbcnt || pending)
		dd_out(1);

	/*
	 * If the file ends with a hole, ftruncate it to extend its size
	 * up to the end of the hole (without having to write any data).
	 */
	if (out.seek_offset > 0 && (out.flags & ISTRUNC)) {
		if (ftruncate(out.fd, out.seek_offset) == -1)
			err(1, "truncating %s", out.name);
	}

	if (ddflags & C_FSYNC) {
		if (fsync(out.fd) == -1)
			err(1, "fsyncing %s", out.name);
	} else if (ddflags & C_FDATASYNC) {
		if (fdatasync(out.fd) == -1)
			err(1, "fdatasyncing %s", out.name);
	}
}