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
struct line6_dump_request {int /*<<< orphan*/  timer; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int line6_dumpreq_initbuf (struct line6_dump_request*,void const*,size_t,int /*<<< orphan*/ ) ; 

int line6_dumpreq_init(struct line6_dump_request *l6dr, const void *buf,
		       size_t len)
{
	int ret;
	ret = line6_dumpreq_initbuf(l6dr, buf, len, 0);
	if (ret < 0)
		return ret;
	init_waitqueue_head(&l6dr->wait);
	init_timer(&l6dr->timer);
	return 0;
}