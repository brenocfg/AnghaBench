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
struct lltable {struct ifnet* llt_ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */

struct ifnet *
lltable_get_ifp(const struct lltable *llt)
{
	return (llt->llt_ifp);
}