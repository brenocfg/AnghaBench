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
struct line6_dump_request {TYPE_1__* reqbufs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void line6_dumpreq_destructbuf(struct line6_dump_request *l6dr, int num)
{
	if (l6dr == NULL)
		return;
	if (l6dr->reqbufs[num].buffer == NULL)
		return;
	kfree(l6dr->reqbufs[num].buffer);
	l6dr->reqbufs[num].buffer = NULL;
}