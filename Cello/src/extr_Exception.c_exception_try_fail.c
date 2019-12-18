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
struct Exception {int active; } ;

/* Variables and functions */
 int /*<<< orphan*/  Exception ; 
 struct Exception* current (int /*<<< orphan*/ ) ; 

void exception_try_fail(void) {
  struct Exception* e = current(Exception);
  e->active = true;
}