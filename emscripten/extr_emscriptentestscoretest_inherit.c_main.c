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
struct TYPE_4__ {int x1; int x2; int y; } ;
struct TYPE_3__ {int x1; int x2; } ;
typedef  TYPE_1__ Parent ;
typedef  TYPE_2__ Child ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int) ; 

int main() {
  Parent a;
  a.x1 = 50;
  a.x2 = 87;
  Child b;
  b.x1 = 78;
  b.x2 = 550;
  b.y = 101;
  Child* c = (Child*)&a;
  c->x1++;
  c = &b;
  c->y--;
  printf("*%d,%d,%d,%d,%d,%d,%d*\n", a.x1, a.x2, b.x1, b.x2, b.y, c->x1, c->x2);
  return 0;
}