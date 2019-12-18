#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* stmt_ann_t ;
struct TYPE_3__ {int modified; } ;

/* Variables and functions */
 TYPE_1__* stmt_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
stmt_modified_p (tree t)
{
  stmt_ann_t ann = stmt_ann (t);

  /* Note that if the statement doesn't yet have an annotation, we consider it
     modified.  This will force the next call to update_stmt_operands to scan 
     the statement.  */
  return ann ? ann->modified : true;
}