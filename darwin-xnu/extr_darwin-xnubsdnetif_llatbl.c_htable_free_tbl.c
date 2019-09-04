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
struct lltable {struct lltable* lle_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct lltable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_LLTABLE ; 

__attribute__((used)) static void
htable_free_tbl(struct lltable *llt)
{

	FREE(llt->lle_head, M_LLTABLE);
	FREE(llt, M_LLTABLE);
}