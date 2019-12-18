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
struct TYPE_3__ {int /*<<< orphan*/  hti; } ;
typedef  TYPE_1__ referenced_var_iterator ;

/* Variables and functions */
 int end_htab_p (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
end_referenced_vars_p (referenced_var_iterator *iter)
{
  return end_htab_p (&iter->hti);
}