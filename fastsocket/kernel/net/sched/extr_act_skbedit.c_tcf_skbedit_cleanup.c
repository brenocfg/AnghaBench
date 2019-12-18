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
struct tcf_skbedit {int /*<<< orphan*/  common; } ;
struct tc_action {struct tcf_skbedit* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  skbedit_hash_info ; 
 int tcf_hash_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int tcf_skbedit_cleanup(struct tc_action *a, int bind)
{
	struct tcf_skbedit *d = a->priv;

	if (d)
		return tcf_hash_release(&d->common, bind, &skbedit_hash_info);
	return 0;
}