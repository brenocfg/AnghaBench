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
struct function {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_safe_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct function*) ; 
 struct function* cfun ; 
 int /*<<< orphan*/  cfun_stack ; 
 int /*<<< orphan*/  function_p ; 
 int /*<<< orphan*/  heap ; 

void
push_cfun (struct function *new_cfun)
{
  VEC_safe_push (function_p, heap, cfun_stack, cfun);
  cfun = new_cfun;
}