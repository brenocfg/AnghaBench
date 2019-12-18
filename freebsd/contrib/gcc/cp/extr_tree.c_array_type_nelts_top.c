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
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  array_type_nelts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  sizetype ; 

tree
array_type_nelts_top (tree type)
{
  return fold_build2 (PLUS_EXPR, sizetype,
		      array_type_nelts (type),
		      integer_one_node);
}