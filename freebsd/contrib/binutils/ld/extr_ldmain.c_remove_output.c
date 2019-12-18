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
 int /*<<< orphan*/  bfd_cache_close (scalar_t__) ; 
 scalar_t__ delete_output_file_on_failure ; 
 scalar_t__ output_bfd ; 
 scalar_t__ output_filename ; 
 int /*<<< orphan*/  unlink_if_ordinary (scalar_t__) ; 

__attribute__((used)) static void
remove_output (void)
{
  if (output_filename)
    {
      if (output_bfd)
	bfd_cache_close (output_bfd);
      if (delete_output_file_on_failure)
	unlink_if_ordinary (output_filename);
    }
}