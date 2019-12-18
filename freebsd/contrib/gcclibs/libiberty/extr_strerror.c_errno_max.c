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

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * error_names ; 
 int /*<<< orphan*/  init_error_tables () ; 
 int /*<<< orphan*/  num_error_names ; 
 int /*<<< orphan*/  sys_nerr ; 

int
errno_max (void)
{
  int maxsize;

  if (error_names == NULL)
    {
      init_error_tables ();
    }
  maxsize = MAX (sys_nerr, num_error_names);
  return (maxsize - 1);
}