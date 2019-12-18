#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cookie; } ;
struct TYPE_4__ {TYPE_1__ ike; } ;
struct pf_app_state {TYPE_2__ u; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */

__attribute__((used)) static int
pf_ike_compare(struct pf_app_state *a, struct pf_app_state *b)
{
	int64_t d = a->u.ike.cookie - b->u.ike.cookie;
	return ((d > 0) ? 1 : ((d < 0) ? -1 : 0));
}