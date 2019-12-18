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
struct symtab_and_line {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_p; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ args_for_catchpoint_enable ;

/* Variables and functions */
 struct symtab_and_line* target_enable_exception_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cover_target_enable_exception_callback (void *arg)
{
  args_for_catchpoint_enable *args = arg;
  struct symtab_and_line *sal;
  sal = target_enable_exception_callback (args->kind, args->enable_p);
  if (sal == NULL)
    return 0;
  else if (sal == (struct symtab_and_line *) -1)
    return -1;
  else
    return 1;			/*is valid */
}