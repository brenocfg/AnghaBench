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
struct coff_sfile {int /*<<< orphan*/  scope; } ;
struct coff_section {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_TYPE_COMPUNIT ; 
 int /*<<< orphan*/  walk_tree_scope (struct coff_section*,struct coff_sfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
walk_tree_sfile (struct coff_section *section, struct coff_sfile *sfile)
{
  walk_tree_scope (section, sfile, sfile->scope, 0, BLOCK_TYPE_COMPUNIT);
}