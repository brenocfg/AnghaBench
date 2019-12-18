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
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/ * stdoutput ; 

void
output_file_close (char *filename)
{
  bfd_boolean res;

  if (stdoutput == NULL)
    return;
    
  /* Close the bfd.  */
  res = bfd_close (stdoutput);

  /* Prevent an infinite loop - if the close failed we will call as_fatal
     which will call xexit() which may call this function again...  */
  stdoutput = NULL;

  if (! res)
    as_fatal (_("can't close %s: %s"), filename,
	      bfd_errmsg (bfd_get_error ()));
}