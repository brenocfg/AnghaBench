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
struct TYPE_3__ {int bulk_read; } ;
struct TYPE_4__ {scalar_t__ buf; } ;
struct ubifs_info {int bulk_read; scalar_t__ max_bu_buf_len; TYPE_1__ mount_opts; TYPE_2__ bu; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 scalar_t__ UBIFS_KMALLOC_OK ; 
 int __GFP_NOWARN ; 
 scalar_t__ kmalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_warn (char*,scalar_t__) ; 

__attribute__((used)) static void bu_init(struct ubifs_info *c)
{
	ubifs_assert(c->bulk_read == 1);

	if (c->bu.buf)
		return; /* Already initialized */

again:
	c->bu.buf = kmalloc(c->max_bu_buf_len, GFP_KERNEL | __GFP_NOWARN);
	if (!c->bu.buf) {
		if (c->max_bu_buf_len > UBIFS_KMALLOC_OK) {
			c->max_bu_buf_len = UBIFS_KMALLOC_OK;
			goto again;
		}

		/* Just disable bulk-read */
		ubifs_warn("Cannot allocate %d bytes of memory for bulk-read, "
			   "disabling it", c->max_bu_buf_len);
		c->mount_opts.bulk_read = 1;
		c->bulk_read = 0;
		return;
	}
}