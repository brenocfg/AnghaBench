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
typedef  TYPE_1__* var_ann_t ;
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int used; } ;

/* Variables and functions */
 TYPE_1__* get_var_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
set_is_used (tree var)
{
  var_ann_t ann = get_var_ann (var);
  ann->used = 1;
}