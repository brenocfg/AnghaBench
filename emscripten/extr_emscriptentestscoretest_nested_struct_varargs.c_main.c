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
struct B {double x; } ;
struct A {int x; } ;
struct C {char* c; struct B b; struct A a; } ;

/* Variables and functions */
 int /*<<< orphan*/  foo (int /*<<< orphan*/ ,struct C) ; 

int main() {
  struct A a = {
    .x = 42,
  };
  struct B b = {
    .x = 42.314,
  };
  struct C c = {
    .a = a,
    .b = b,
    .c = "nicetest",
  };
  foo(0, c);
  return 0;
}