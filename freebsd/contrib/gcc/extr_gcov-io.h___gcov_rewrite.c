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
struct TYPE_2__ {int mode; int /*<<< orphan*/  file; scalar_t__ offset; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__ gcov_var ; 

__attribute__((used)) static inline void
gcov_rewrite (void)
{
  gcc_assert (gcov_var.mode > 0);
  gcov_var.mode = -1;
  gcov_var.start = 0;
  gcov_var.offset = 0;
  fseek (gcov_var.file, 0L, SEEK_SET);
}