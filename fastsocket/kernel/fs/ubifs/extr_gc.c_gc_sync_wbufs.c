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
struct ubifs_info {int jhead_cnt; TYPE_1__* jheads; } ;
struct TYPE_2__ {int /*<<< orphan*/  wbuf; } ;

/* Variables and functions */
 int GCHD ; 
 int ubifs_wbuf_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gc_sync_wbufs(struct ubifs_info *c)
{
	int err, i;

	for (i = 0; i < c->jhead_cnt; i++) {
		if (i == GCHD)
			continue;
		err = ubifs_wbuf_sync(&c->jheads[i].wbuf);
		if (err)
			return err;
	}
	return 0;
}