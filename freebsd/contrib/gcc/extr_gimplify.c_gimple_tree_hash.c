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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  hashval_t ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ elt_t ;

/* Variables and functions */
 int /*<<< orphan*/  iterative_hash_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
gimple_tree_hash (const void *p)
{
  tree t = ((const elt_t *) p)->val;
  return iterative_hash_expr (t, 0);
}