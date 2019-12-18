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
struct TYPE_2__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 TYPE_1__* dp_genl_families ; 
 int /*<<< orphan*/  genl_unregister_family (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dp_unregister_genl(int n_families)
{
	int i;

	for (i = 0; i < n_families; i++)
		genl_unregister_family(dp_genl_families[i].family);
}