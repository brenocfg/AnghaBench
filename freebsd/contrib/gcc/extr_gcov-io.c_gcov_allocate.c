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
struct TYPE_2__ {size_t alloc; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 size_t GCOV_BLOCK_SIZE ; 
 TYPE_1__ gcov_var ; 
 int /*<<< orphan*/  xrealloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
gcov_allocate (unsigned length)
{
  size_t new_size = gcov_var.alloc;
  
  if (!new_size)
    new_size = GCOV_BLOCK_SIZE;
  new_size += length;
  new_size *= 2;
  
  gcov_var.alloc = new_size;
  gcov_var.buffer = xrealloc (gcov_var.buffer, new_size << 2);
}