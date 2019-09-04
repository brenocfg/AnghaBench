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
struct hsearch_data {TYPE_1__* __tab; } ;
struct TYPE_2__ {struct TYPE_2__* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void __hdestroy_r(struct hsearch_data *htab)
{
	if (htab->__tab) free(htab->__tab->entries);
	free(htab->__tab);
	htab->__tab = 0;
}