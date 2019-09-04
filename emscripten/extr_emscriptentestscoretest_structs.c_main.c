#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int x; int y; } ;
typedef  TYPE_1__ S ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int) ; 

int main() {
  S a, b;
  a.x = 5;
  a.y = 6;
  b.x = 101;
  b.y = 7009;
  S *c, *d;
  c = &a;
  c->x *= 2;
  c = &b;
  c->y -= 1;
  d = c;
  d->y += 10;
  printf("*%d,%d,%d,%d,%d,%d,%d,%d*\n", a.x, a.y, b.x, b.y, c->x, c->y, d->x,
         d->y);
  return 0;
}