#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * jmp; } ;
typedef  TYPE_1__ jmp_state ;
typedef  int /*<<< orphan*/  jmp_buf ;

/* Variables and functions */
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  second_func (TYPE_1__*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

void first_func(jmp_state* s) {
  jmp_buf* prev_jmp = s->jmp;
  jmp_buf c_jmp;
  volatile int once = 0;

  if (setjmp(c_jmp) == 0) {
    printf("Normal execution path of first function!\n");

    s->jmp = &c_jmp;
    second_func(s);
  } else {
    printf("Exception execution path of first function! %d\n", once);

    if (!once) {
      printf("Calling longjmp the second time!\n");
      once = 1;
      longjmp(*(s->jmp), 1);
    }
  }
}