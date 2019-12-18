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
 int /*<<< orphan*/  bfd_cache_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * output_bfd ; 
 int /*<<< orphan*/ * output_file ; 
 int /*<<< orphan*/ * output_filename ; 
 int /*<<< orphan*/  unlink_if_ordinary (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
remove_output (void)
{
  if (output_filename != NULL)
    {
      if (output_bfd != NULL)
	bfd_cache_close (output_bfd);
      if (output_file != NULL)
	fclose (output_file);
      unlink_if_ordinary (output_filename);
    }
}