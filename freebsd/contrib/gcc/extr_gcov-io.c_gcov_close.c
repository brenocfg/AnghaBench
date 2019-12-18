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
struct TYPE_2__ {scalar_t__ mode; int error; scalar_t__ buffer; scalar_t__ alloc; scalar_t__ length; scalar_t__ file; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 TYPE_1__ gcov_var ; 
 int /*<<< orphan*/  gcov_write_block (scalar_t__) ; 

int
gcov_close (void)
{
  if (gcov_var.file)
    {
#if !IN_GCOV
      if (gcov_var.offset && gcov_var.mode < 0)
	gcov_write_block (gcov_var.offset);
#endif
      fclose (gcov_var.file);
      gcov_var.file = 0;
      gcov_var.length = 0;
    }
#if !IN_LIBGCOV
  free (gcov_var.buffer);
  gcov_var.alloc = 0;
  gcov_var.buffer = 0;
#endif
  gcov_var.mode = 0;
  return gcov_var.error;
}