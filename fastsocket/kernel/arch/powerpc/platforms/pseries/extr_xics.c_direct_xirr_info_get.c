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
struct TYPE_3__ {int /*<<< orphan*/  word; } ;
struct TYPE_4__ {TYPE_1__ xirr; } ;

/* Variables and functions */
 unsigned int in_be32 (int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 
 TYPE_2__** xics_per_cpu ; 

__attribute__((used)) static inline unsigned int direct_xirr_info_get(void)
{
	int cpu = smp_processor_id();

	return in_be32(&xics_per_cpu[cpu]->xirr.word);
}