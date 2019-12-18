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
struct lltable {int (* llt_foreach_entry ) (struct lltable*,int /*<<< orphan*/ *,void*) ;} ;
typedef  int /*<<< orphan*/  llt_foreach_cb_t ;

/* Variables and functions */
 int stub1 (struct lltable*,int /*<<< orphan*/ *,void*) ; 

int
lltable_foreach_lle(struct lltable *llt, llt_foreach_cb_t *f, void *farg)
{
	return (llt->llt_foreach_entry(llt, f, farg));
}