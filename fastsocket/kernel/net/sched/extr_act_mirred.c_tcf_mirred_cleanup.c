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
struct tcf_mirred {int dummy; } ;
struct tc_action {struct tcf_mirred* priv; } ;

/* Variables and functions */
 int tcf_mirred_release (struct tcf_mirred*,int) ; 

__attribute__((used)) static int tcf_mirred_cleanup(struct tc_action *a, int bind)
{
	struct tcf_mirred *m = a->priv;

	if (m)
		return tcf_mirred_release(m, bind);
	return 0;
}