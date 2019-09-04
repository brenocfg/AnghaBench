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
struct llentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct llentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLE_LOCK_DESTROY (struct llentry*) ; 
 int /*<<< orphan*/  LLE_REQ_DESTROY (struct llentry*) ; 
 int /*<<< orphan*/  M_LLTABLE ; 

__attribute__((used)) static void
in6_lltable_destroy_lle_unlocked(struct llentry *lle)
{
	LLE_LOCK_DESTROY(lle);
	LLE_REQ_DESTROY(lle);
	FREE(lle, M_LLTABLE);
}