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
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  addr64_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_OPTIONS_REMOVE ; 
 int /*<<< orphan*/  pmap_remove_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pmap_remove(
	pmap_t		map,
	addr64_t	s64,
	addr64_t	e64)
{
	pmap_remove_options(map, s64, e64, PMAP_OPTIONS_REMOVE);
}