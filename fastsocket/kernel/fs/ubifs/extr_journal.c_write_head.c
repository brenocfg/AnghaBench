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
struct ubifs_wbuf {int lnum; int offs; int used; } ;
struct ubifs_info {TYPE_1__* jheads; } ;
struct TYPE_2__ {struct ubifs_wbuf wbuf; } ;

/* Variables and functions */
 int GCHD ; 
 int /*<<< orphan*/  dbg_jhead (int) ; 
 int /*<<< orphan*/  dbg_jnl (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int ubifs_wbuf_sync_nolock (struct ubifs_wbuf*) ; 
 int ubifs_wbuf_write_nolock (struct ubifs_wbuf*,void*,int) ; 

__attribute__((used)) static int write_head(struct ubifs_info *c, int jhead, void *buf, int len,
		      int *lnum, int *offs, int sync)
{
	int err;
	struct ubifs_wbuf *wbuf = &c->jheads[jhead].wbuf;

	ubifs_assert(jhead != GCHD);

	*lnum = c->jheads[jhead].wbuf.lnum;
	*offs = c->jheads[jhead].wbuf.offs + c->jheads[jhead].wbuf.used;
	dbg_jnl("jhead %s, LEB %d:%d, len %d",
		dbg_jhead(jhead), *lnum, *offs, len);

	err = ubifs_wbuf_write_nolock(wbuf, buf, len);
	if (err)
		return err;
	if (sync)
		err = ubifs_wbuf_sync_nolock(wbuf);
	return err;
}