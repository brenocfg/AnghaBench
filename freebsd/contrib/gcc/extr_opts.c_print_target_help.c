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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CL_TARGET ; 
 int CL_UNDOCUMENTED ; 
 char* _ (char*) ; 
 TYPE_1__* cl_options ; 
 unsigned int cl_options_count ; 
 int /*<<< orphan*/  print_filtered_help (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
print_target_help (void)
{
  unsigned int i;
  static bool displayed = false;

  /* Avoid double printing for --help --target-help.  */
  if (displayed)
    return;

  displayed = true;
  for (i = 0; i < cl_options_count; i++)
    if ((cl_options[i].flags & (CL_TARGET | CL_UNDOCUMENTED)) == CL_TARGET)
      {
	printf (_("\nTarget specific options:\n"));
	print_filtered_help (CL_TARGET);
	break;
      }
}