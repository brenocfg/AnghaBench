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
struct map_symbol {int unfolded; int has_children; } ;

/* Variables and functions */

__attribute__((used)) static void map_symbol__set_folding(struct map_symbol *ms, bool unfold)
{
	ms->unfolded = unfold ? ms->has_children : false;
}