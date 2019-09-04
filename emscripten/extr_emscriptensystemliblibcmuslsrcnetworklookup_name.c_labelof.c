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
struct in6_addr {int dummy; } ;
struct TYPE_2__ {int label; } ;

/* Variables and functions */
 TYPE_1__* policyof (struct in6_addr const*) ; 

__attribute__((used)) static int labelof(const struct in6_addr *a)
{
	return policyof(a)->label;
}