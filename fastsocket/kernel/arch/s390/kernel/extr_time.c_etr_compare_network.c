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
struct TYPE_2__ {scalar_t__ net_id; } ;
struct etr_aib {TYPE_1__ edf1; } ;

/* Variables and functions */

__attribute__((used)) static int etr_compare_network(struct etr_aib *aib1, struct etr_aib *aib2)
{
	// FIXME: any other fields we have to compare?
	return aib1->edf1.net_id == aib2->edf1.net_id;
}