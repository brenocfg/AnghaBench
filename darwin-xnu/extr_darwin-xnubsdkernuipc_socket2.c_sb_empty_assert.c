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
struct sockbuf {scalar_t__ sb_cc; scalar_t__ sb_mbcnt; int /*<<< orphan*/ * sb_lastrecord; int /*<<< orphan*/ * sb_mbtail; int /*<<< orphan*/ * sb_mb; int /*<<< orphan*/  sb_so; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,char const*,struct sockbuf*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
sb_empty_assert(struct sockbuf *sb, const char *where)
{
	if (!(sb->sb_cc == 0 && sb->sb_mb == NULL && sb->sb_mbcnt == 0 &&
	    sb->sb_mbtail == NULL && sb->sb_lastrecord == NULL)) {
		panic("%s: sb %p so %p cc %d mbcnt %d mb %p mbtail %p "
		    "lastrecord %p\n", where, sb, sb->sb_so, sb->sb_cc,
		    sb->sb_mbcnt, sb->sb_mb, sb->sb_mbtail,
		    sb->sb_lastrecord);
		/* NOTREACHED */
	}
}