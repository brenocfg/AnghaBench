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
struct TYPE_3__ {int /*<<< orphan*/ * jmp; } ;
typedef  TYPE_1__ jmp_state ;

/* Variables and functions */
 int /*<<< orphan*/  stack_manipulate_func (TYPE_1__*,int /*<<< orphan*/ ) ; 

int main(int argc, char* argv[]) {
  jmp_state s;
  s.jmp = NULL;
  stack_manipulate_func(&s, 0);

  return 0;
}