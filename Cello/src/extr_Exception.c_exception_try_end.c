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
struct Exception {scalar_t__ depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  Exception ; 
 int /*<<< orphan*/  abort () ; 
 struct Exception* current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void exception_try_end(void) {
  struct Exception* e = current(Exception);
  if (e->depth == 0) {
    fprintf(stderr, "Cello Fatal Error: Exception Buffer Underflow!\n");
    abort();
  }
  e->depth--;
}