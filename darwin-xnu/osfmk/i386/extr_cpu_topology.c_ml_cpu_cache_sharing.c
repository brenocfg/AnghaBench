#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nlcpus; } ;
typedef  TYPE_2__ x86_cpu_cache_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {TYPE_2__** caches; } ;
struct TYPE_8__ {TYPE_1__ lcpu; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_cpus; } ;

/* Variables and functions */
 unsigned int MAX_CACHE_DEPTH ; 
 TYPE_4__* current_cpu_datap () ; 
 TYPE_3__ machine_info ; 

uint64_t
ml_cpu_cache_sharing(unsigned int level)
{
	x86_cpu_cache_t	*cachep;

	if (level == 0) {
		return machine_info.max_cpus;
	} else if ( 1 <= level && level <= MAX_CACHE_DEPTH) {
		cachep = current_cpu_datap()->lcpu.caches[level-1];
		return cachep ? cachep->nlcpus : 0;
	} else {
		return 0;
	}
}