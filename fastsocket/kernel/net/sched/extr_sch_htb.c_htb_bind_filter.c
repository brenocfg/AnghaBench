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
typedef  int /*<<< orphan*/  u32 ;
struct htb_class {int /*<<< orphan*/  filter_cnt; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct htb_class* htb_find (int /*<<< orphan*/ ,struct Qdisc*) ; 

__attribute__((used)) static unsigned long htb_bind_filter(struct Qdisc *sch, unsigned long parent,
				     u32 classid)
{
	struct htb_class *cl = htb_find(classid, sch);

	/*if (cl && !cl->level) return 0;
	   The line above used to be there to prevent attaching filters to
	   leaves. But at least tc_index filter uses this just to get class
	   for other reasons so that we have to allow for it.
	   ----
	   19.6.2002 As Werner explained it is ok - bind filter is just
	   another way to "lock" the class - unlike "get" this lock can
	   be broken by class during destroy IIUC.
	 */
	if (cl)
		cl->filter_cnt++;
	return (unsigned long)cl;
}