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
struct line6_dump_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE6_DUMP_CURRENT ; 
 int /*<<< orphan*/  line6_dump_started (struct line6_dump_request*,int /*<<< orphan*/ ) ; 

void line6_invalidate_current(struct line6_dump_request *l6dr)
{
	line6_dump_started(l6dr, LINE6_DUMP_CURRENT);
}