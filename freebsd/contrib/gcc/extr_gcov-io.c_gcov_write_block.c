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
struct TYPE_2__ {int error; unsigned int start; unsigned int offset; int /*<<< orphan*/  file; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int fwrite (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ gcov_var ; 

__attribute__((used)) static void
gcov_write_block (unsigned size)
{
  if (fwrite (gcov_var.buffer, size << 2, 1, gcov_var.file) != 1)
    gcov_var.error = 1;
  gcov_var.start += size;
  gcov_var.offset -= size;
}