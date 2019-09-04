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
struct TYPE_4__ {int length; TYPE_1__* value; } ;
typedef  TYPE_2__ Tuple ;
struct TYPE_3__ {int int32; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int) ; 

int main() {
  Tuple T[10];
  Tuple *t = &T[0];

  t->length = 4;
  t->value->int32 = 100;

  printf("(%d, %d)\n", t->length, t->value->int32);
  return 0;
}