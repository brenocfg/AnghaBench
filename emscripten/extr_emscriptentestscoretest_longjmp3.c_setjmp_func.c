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
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

void setjmp_func(jmp_state* s, int level) {
  jmp_buf* prev_jmp = s->jmp;
  jmp_buf c_jmp;

  if (level == 2) {
    printf("level is 2, perform longjmp!\n");
    longjmp(*(s->jmp), 1);
  }

  if (setjmp(c_jmp) == 0) {
    printf("setjmp normal execution path, level: %d\n", level);
    s->jmp = &c_jmp;
    setjmp_func(s, level + 1);
  } else {
    printf("setjmp exception execution path, level: %d\n", level);
    if (prev_jmp) {
      printf("prev_jmp is not empty, continue with longjmp!\n");
      s->jmp = prev_jmp;
      longjmp(*(s->jmp), 1);
    }
  }

  printf("Exiting setjmp function, level: %d\n", level);
}