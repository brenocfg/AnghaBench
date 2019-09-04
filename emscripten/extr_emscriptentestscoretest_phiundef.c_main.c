#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int a; } ;
struct TYPE_4__ {TYPE_1__ c; } ;
struct my_struct {TYPE_2__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 
 int state ; 

int main(int argc, char **argv) {
  struct my_struct r;

  state = 0;

  for (int i = 0; i < argc + 10; i++) {
    if (state % 2 == 0)
      r.e.c.a = 3;
    else
      printf("%d\n", r.e.c.a);
    state++;
  }
  return 0;
}