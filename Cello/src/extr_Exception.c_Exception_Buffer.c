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
struct Exception {int depth; int /*<<< orphan*/ ** buffers; } ;
typedef  int /*<<< orphan*/  jmp_buf ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static jmp_buf* Exception_Buffer(struct Exception* e) {
  if (e->depth == 0) {
    fprintf(stderr, "Cello Fatal Error: Exception Buffer Out of Bounds!\n");
    abort();
  }
  return e->buffers[e->depth-1];
}