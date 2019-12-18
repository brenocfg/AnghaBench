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
struct lguest {TYPE_1__* pgdirs; } ;
struct TYPE_2__ {unsigned long gpgdir; scalar_t__ pgdir; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 

__attribute__((used)) static unsigned int find_pgdir(struct lguest *lg, unsigned long pgtable)
{
	unsigned int i;
	for (i = 0; i < ARRAY_SIZE(lg->pgdirs); i++)
		if (lg->pgdirs[i].pgdir && lg->pgdirs[i].gpgdir == pgtable)
			break;
	return i;
}