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
struct loop {int dummy; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {struct loop* loop_father; } ;

/* Variables and functions */
 TYPE_1__* bb_for_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct loop *
loop_containing_stmt (tree stmt)
{
  basic_block bb = bb_for_stmt (stmt);
  if (!bb)
    return NULL;

  return bb->loop_father;
}