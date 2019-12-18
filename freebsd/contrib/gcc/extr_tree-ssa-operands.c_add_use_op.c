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
typedef  int /*<<< orphan*/  use_optype_p ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_OPTYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APPEND_OP_AFTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INITIALIZE_USE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USE_OP_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use ; 

__attribute__((used)) static inline void
add_use_op (tree stmt, tree *op, use_optype_p *last)
{
  use_optype_p new;

  ALLOC_OPTYPE (new, use);
  INITIALIZE_USE (USE_OP_PTR (new), op, stmt);
  APPEND_OP_AFTER (new, *last);  
}