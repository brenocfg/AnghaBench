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
struct ingress_qdisc_data {int /*<<< orphan*/  filter_list; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct ingress_qdisc_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  tcf_destroy_chain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ingress_destroy(struct Qdisc *sch)
{
	struct ingress_qdisc_data *p = qdisc_priv(sch);

	tcf_destroy_chain(&p->filter_list);
}