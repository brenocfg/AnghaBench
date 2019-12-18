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

/* Variables and functions */
 int /*<<< orphan*/  copy_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_dup_lang_specific_decl (int /*<<< orphan*/ ) ; 

tree
copy_decl (tree decl)
{
  tree copy;

  copy = copy_node (decl);
  cxx_dup_lang_specific_decl (copy);
  return copy;
}