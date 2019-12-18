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
struct htb_class {scalar_t__ refcnt; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  htb_destroy_class (struct Qdisc*,struct htb_class*) ; 

__attribute__((used)) static void htb_put(struct Qdisc *sch, unsigned long arg)
{
	struct htb_class *cl = (struct htb_class *)arg;

	if (--cl->refcnt == 0)
		htb_destroy_class(sch, cl);
}