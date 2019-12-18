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
struct ubifs_jhead {int dummy; } ;
struct ubifs_info {int jhead_cnt; TYPE_2__* jheads; } ;
struct TYPE_3__ {int jhead; int no_timer; int /*<<< orphan*/  dtype; int /*<<< orphan*/ * sync_callback; } ;
struct TYPE_4__ {TYPE_1__ wbuf; int /*<<< orphan*/  buds_list; } ;

/* Variables and functions */
 size_t BASEHD ; 
 int ENOMEM ; 
 size_t GCHD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UBI_LONGTERM ; 
 int /*<<< orphan*/  UBI_SHORTTERM ; 
 int /*<<< orphan*/  bud_wbuf_callback ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ubifs_wbuf_init (struct ubifs_info*,TYPE_1__*) ; 

__attribute__((used)) static int alloc_wbufs(struct ubifs_info *c)
{
	int i, err;

	c->jheads = kzalloc(c->jhead_cnt * sizeof(struct ubifs_jhead),
			   GFP_KERNEL);
	if (!c->jheads)
		return -ENOMEM;

	/* Initialize journal heads */
	for (i = 0; i < c->jhead_cnt; i++) {
		INIT_LIST_HEAD(&c->jheads[i].buds_list);
		err = ubifs_wbuf_init(c, &c->jheads[i].wbuf);
		if (err)
			return err;

		c->jheads[i].wbuf.sync_callback = &bud_wbuf_callback;
		c->jheads[i].wbuf.jhead = i;
	}

	c->jheads[BASEHD].wbuf.dtype = UBI_SHORTTERM;
	/*
	 * Garbage Collector head likely contains long-term data and
	 * does not need to be synchronized by timer.
	 */
	c->jheads[GCHD].wbuf.dtype = UBI_LONGTERM;
	c->jheads[GCHD].wbuf.no_timer = 1;

	return 0;
}