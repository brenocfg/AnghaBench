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
typedef  int /*<<< orphan*/  u_int ;
struct sockaddr {int dummy; } ;
struct lltable {struct llentry* (* llt_alloc_entry ) (struct lltable*,int /*<<< orphan*/ ,struct sockaddr const*) ;} ;
struct llentry {int dummy; } ;

/* Variables and functions */
 struct llentry* stub1 (struct lltable*,int /*<<< orphan*/ ,struct sockaddr const*) ; 

struct llentry *
lltable_alloc_entry(struct lltable *llt, u_int flags,
    const struct sockaddr *l3addr)
{
	return (llt->llt_alloc_entry(llt, flags, l3addr));
}