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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  dump_info_p ;

/* Variables and functions */
 scalar_t__ TREE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PROTECTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_string_field (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
dump_access (dump_info_p di, tree t)
{
  if (TREE_PROTECTED(t))
    dump_string_field (di, "accs", "prot");
  else if (TREE_PRIVATE(t))
    dump_string_field (di, "accs", "priv");
  else
    dump_string_field (di, "accs", "pub");
}