#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  INTERNAL ; 
 TYPE_1__* Targ_NewGN (char*) ; 
 TYPE_1__* cached_realpaths ; 

__attribute__((used)) static GNode *
get_cached_realpaths(void)
{

    if (!cached_realpaths) {
	cached_realpaths = Targ_NewGN("Realpath");
#ifndef DEBUG_REALPATH_CACHE
	cached_realpaths->flags = INTERNAL;
#endif
    }

    return cached_realpaths;
}