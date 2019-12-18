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
struct cypress_buf {struct cypress_buf* buf_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cypress_buf*) ; 

__attribute__((used)) static void cypress_buf_free(struct cypress_buf *cb)
{
	if (cb) {
		kfree(cb->buf_buf);
		kfree(cb);
	}
}