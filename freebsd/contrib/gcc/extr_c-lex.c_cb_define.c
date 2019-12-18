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
struct line_map {int dummy; } ;
typedef  int /*<<< orphan*/  source_location ;
typedef  int /*<<< orphan*/  cpp_reader ;
typedef  int /*<<< orphan*/  cpp_hashnode ;
struct TYPE_2__ {int /*<<< orphan*/  (* define ) (int /*<<< orphan*/ ,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SOURCE_LINE (struct line_map const*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpp_macro_definition (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* debug_hooks ; 
 int /*<<< orphan*/  line_table ; 
 struct line_map* linemap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
cb_define (cpp_reader *pfile, source_location loc, cpp_hashnode *node)
{
  const struct line_map *map = linemap_lookup (&line_table, loc);
  (*debug_hooks->define) (SOURCE_LINE (map, loc),
			  (const char *) cpp_macro_definition (pfile, node));
}