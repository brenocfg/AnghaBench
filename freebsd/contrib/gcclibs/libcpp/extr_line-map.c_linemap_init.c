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
struct line_maps {int last_listed; int trace_includes; scalar_t__ max_column_hint; scalar_t__ highest_line; scalar_t__ highest_location; scalar_t__ cache; scalar_t__ depth; scalar_t__ used; scalar_t__ allocated; int /*<<< orphan*/ * maps; } ;

/* Variables and functions */

void
linemap_init (struct line_maps *set)
{
  set->maps = NULL;
  set->allocated = 0;
  set->used = 0;
  set->last_listed = -1;
  set->trace_includes = false;
  set->depth = 0;
  set->cache = 0;
  set->highest_location = 0;
  set->highest_line = 0;
  set->max_column_hint = 0;
}