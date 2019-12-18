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
struct parsed_partitions {int limit; int /*<<< orphan*/  name; TYPE_1__* parts; } ;
typedef  void* sector_t ;
struct TYPE_2__ {void* size; void* from; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
put_partition(struct parsed_partitions *p, int n, sector_t from, sector_t size)
{
	if (n < p->limit) {
		p->parts[n].from = from;
		p->parts[n].size = size;
		printk(" %s%d", p->name, n);
	}
}