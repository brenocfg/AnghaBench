#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  addr6; } ;
struct llentry {TYPE_1__ r_l3addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  in6_lltable_hash_dst (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
in6_lltable_hash(const struct llentry *lle, uint32_t hsize)
{
	return (in6_lltable_hash_dst(&lle->r_l3addr.addr6, hsize));
}