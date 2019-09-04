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

/* Variables and functions */
 void* lck_attr_alloc_init () ; 
 void* lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_rw_init (int /*<<< orphan*/ ,void*,void*) ; 
 void* lle_lock_attr ; 
 void* lle_lock_grp ; 
 int /*<<< orphan*/  lle_lock_grp_attr ; 
 int /*<<< orphan*/  lltable_rwlock ; 
 void* lltable_rwlock_attr ; 
 void* lltable_rwlock_grp ; 
 int /*<<< orphan*/  lltable_rwlock_grp_attr ; 

void
lltable_glbl_init()
{
	lltable_rwlock_grp_attr = lck_grp_attr_alloc_init();
	lltable_rwlock_grp = lck_grp_alloc_init("lltable_rwlock",
	    lltable_rwlock_grp_attr);
	lltable_rwlock_attr = lck_attr_alloc_init();
	lck_rw_init(lltable_rwlock, lltable_rwlock_grp,
	    lltable_rwlock_attr);

	lle_lock_grp_attr = lck_grp_attr_alloc_init();
	lle_lock_grp = lck_grp_alloc_init("lle locks", lle_lock_grp_attr);
	lle_lock_attr = lck_attr_alloc_init();
}