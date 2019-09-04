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
typedef  int /*<<< orphan*/  jmp_buf ;

/* Variables and functions */
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

void stack_manipulate_func(jmp_state* s, int level) {
  jmp_buf buf;

  printf("Entering stack_manipulate_func, level: %d\n", level);

  if (level == 0) {
    s->jmp = &buf;
    if (setjmp(*(s->jmp)) == 0) {
      printf("Setjmp normal execution path, level: %d\n", level);
      stack_manipulate_func(s, level + 1);
    } else {
      printf("Setjmp error execution path, level: %d\n", level);
    }
  } else {
    printf("Perform longjmp at level %d\n", level);
    longjmp(*(s->jmp), 1);
  }

  printf("Exiting stack_manipulate_func, level: %d\n", level);
}