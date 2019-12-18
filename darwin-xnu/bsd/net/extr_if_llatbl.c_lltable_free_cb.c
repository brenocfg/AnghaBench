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
struct llentry {int dummy; } ;
struct llentries {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct llentries*,struct llentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLE_WLOCK (struct llentry*) ; 
 int /*<<< orphan*/  lle_chain ; 

__attribute__((used)) static int
lltable_free_cb(struct lltable *llt, struct llentry *lle, void *farg)
{
#pragma unused(llt)
	struct llentries *dchain;

	dchain = (struct llentries *)farg;

	LLE_WLOCK(lle);
	LIST_INSERT_HEAD(dchain, lle, lle_chain);

	return (0);
}