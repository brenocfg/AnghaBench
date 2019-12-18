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
typedef  int hashval_t ;

/* Variables and functions */
 int TREE_INT_CST_HIGH (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int htab_hash_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
int_cst_hash_hash (const void *x)
{
  tree t = (tree) x;

  return (TREE_INT_CST_HIGH (t) ^ TREE_INT_CST_LOW (t)
	  ^ htab_hash_pointer (TREE_TYPE (t)));
}