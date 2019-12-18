#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* tree ;
typedef  int /*<<< orphan*/  stmt_ann_t ;
struct TYPE_9__ {TYPE_2__* ann; } ;
struct TYPE_10__ {TYPE_3__ common; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_8__ {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ STMT_ANN ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int is_gimple_stmt (TYPE_4__*) ; 

__attribute__((used)) static inline stmt_ann_t
stmt_ann (tree t)
{
#ifdef ENABLE_CHECKING
  gcc_assert (is_gimple_stmt (t));
#endif
  gcc_assert (!t->common.ann || t->common.ann->common.type == STMT_ANN);
  return (stmt_ann_t) t->common.ann;
}