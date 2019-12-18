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
struct line6_dump_request {int ok; int /*<<< orphan*/  timer; TYPE_1__* reqbufs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line6_dumpreq_destructbuf (struct line6_dump_request*,int /*<<< orphan*/ ) ; 

void line6_dumpreq_destruct(struct line6_dump_request *l6dr)
{
	if (l6dr->reqbufs[0].buffer == NULL)
		return;
	line6_dumpreq_destructbuf(l6dr, 0);
	l6dr->ok = 1;
	del_timer_sync(&l6dr->timer);
}