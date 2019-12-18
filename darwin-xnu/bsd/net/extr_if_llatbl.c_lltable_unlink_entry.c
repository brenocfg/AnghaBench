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
struct lltable {int /*<<< orphan*/  (* llt_unlink_entry ) (struct llentry*) ;} ;
struct llentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct llentry*) ; 

void
lltable_unlink_entry(struct lltable *llt, struct llentry *lle)
{
	llt->llt_unlink_entry(lle);
}