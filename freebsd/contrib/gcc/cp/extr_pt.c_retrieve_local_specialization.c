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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 int /*<<< orphan*/  htab_find_with_hash (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer (scalar_t__) ; 
 int /*<<< orphan*/  local_specializations ; 

__attribute__((used)) static tree
retrieve_local_specialization (tree tmpl)
{
  tree spec = (tree) htab_find_with_hash (local_specializations, tmpl,
					  htab_hash_pointer (tmpl));
  return spec ? TREE_PURPOSE (spec) : NULL_TREE;
}