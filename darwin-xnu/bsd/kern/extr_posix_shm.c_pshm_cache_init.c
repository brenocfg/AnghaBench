#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  M_SHM ; 
 int desiredvnodes ; 
 int /*<<< orphan*/  hashinit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pshmhash ; 
 int /*<<< orphan*/  pshmhashtbl ; 

void
pshm_cache_init(void)
{
	pshmhashtbl = hashinit(desiredvnodes / 8, M_SHM, &pshmhash);
}