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
struct sockaddr {int dummy; } ;
struct lltable {int /*<<< orphan*/  (* llt_fill_sa_entry ) (struct llentry const*,struct sockaddr*) ;} ;
struct llentry {struct lltable* lle_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct llentry const*,struct sockaddr*) ; 

void
lltable_fill_sa_entry(const struct llentry *lle, struct sockaddr *sa)
{
	struct lltable *llt;

	llt = lle->lle_tbl;
	llt->llt_fill_sa_entry(lle, sa);
}