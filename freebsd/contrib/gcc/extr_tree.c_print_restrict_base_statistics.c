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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_collisions (int /*<<< orphan*/ ) ; 
 scalar_t__ htab_elements (int /*<<< orphan*/ ) ; 
 scalar_t__ htab_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restrict_base_for_decl ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_restrict_base_statistics (void)
{
  if (htab_elements (restrict_base_for_decl) != 0)
    fprintf (stderr,
	     "RESTRICT_BASE    hash: size %ld, %ld elements, %f collisions\n",
	     (long) htab_size (restrict_base_for_decl),
	     (long) htab_elements (restrict_base_for_decl),
	     htab_collisions (restrict_base_for_decl));
}