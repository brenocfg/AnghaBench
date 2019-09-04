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
struct TYPE_3__ {int /*<<< orphan*/  opaque; void* (* alloc_func ) (int /*<<< orphan*/ ,size_t) ;} ;
typedef  TYPE_1__ MemoryManager ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 void* stub1 (int /*<<< orphan*/ ,size_t) ; 

void* BrotliAllocate(MemoryManager* m, size_t n) {
  void* result = m->alloc_func(m->opaque, n);
  if (!result) exit(EXIT_FAILURE);
  return result;
}