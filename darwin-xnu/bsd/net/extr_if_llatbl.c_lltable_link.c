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
struct lltable {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLTABLE_WLOCK () ; 
 int /*<<< orphan*/  LLTABLE_WUNLOCK () ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct lltable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llt_link ; 
 int /*<<< orphan*/  lltables ; 

void
lltable_link(struct lltable *llt)
{
	LLTABLE_WLOCK();
	SLIST_INSERT_HEAD(&lltables, llt, llt_link);
	LLTABLE_WUNLOCK();
}