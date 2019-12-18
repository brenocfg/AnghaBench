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
struct tcf_defact {int dummy; } ;
struct tc_action {struct tcf_defact* priv; } ;

/* Variables and functions */
 int tcf_simp_release (struct tcf_defact*,int) ; 

__attribute__((used)) static inline int tcf_simp_cleanup(struct tc_action *a, int bind)
{
	struct tcf_defact *d = a->priv;

	if (d)
		return tcf_simp_release(d, bind);
	return 0;
}