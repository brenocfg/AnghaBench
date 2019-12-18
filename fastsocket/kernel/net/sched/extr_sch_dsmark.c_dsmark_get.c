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
struct Qdisc {int dummy; } ;

/* Variables and functions */
 unsigned long TC_H_MIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct Qdisc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static unsigned long dsmark_get(struct Qdisc *sch, u32 classid)
{
	pr_debug("dsmark_get(sch %p,[qdisc %p],classid %x)\n",
		sch, qdisc_priv(sch), classid);

	return TC_H_MIN(classid) + 1;
}