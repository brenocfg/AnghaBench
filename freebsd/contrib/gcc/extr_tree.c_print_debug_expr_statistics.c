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
 int /*<<< orphan*/  debug_expr_for_decl ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_collisions (int /*<<< orphan*/ ) ; 
 scalar_t__ htab_elements (int /*<<< orphan*/ ) ; 
 scalar_t__ htab_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_debug_expr_statistics (void)
{
  fprintf (stderr, "DECL_DEBUG_EXPR  hash: size %ld, %ld elements, %f collisions\n",
	   (long) htab_size (debug_expr_for_decl),
	   (long) htab_elements (debug_expr_for_decl),
	   htab_collisions (debug_expr_for_decl));
}