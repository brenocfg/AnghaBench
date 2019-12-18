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
typedef  scalar_t__ gcov_unsigned_t ;
typedef  scalar_t__ gcov_position_t ;
struct TYPE_2__ {scalar_t__ mode; scalar_t__ start; scalar_t__ length; scalar_t__ offset; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__ gcov_var ; 

void
gcov_sync (gcov_position_t base, gcov_unsigned_t length)
{
  gcc_assert (gcov_var.mode > 0);
  base += length;
  if (base - gcov_var.start <= gcov_var.length)
    gcov_var.offset = base - gcov_var.start;
  else
    {
      gcov_var.offset = gcov_var.length = 0;
      fseek (gcov_var.file, base << 2, SEEK_SET);
      gcov_var.start = ftell (gcov_var.file) >> 2;
    }
}