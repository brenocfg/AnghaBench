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
 scalar_t__ ISTREAM_FILE ; 
 int /*<<< orphan*/ * cpp_pipe ; 
 int /*<<< orphan*/ * cpp_temp_file ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ istream_type ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
close_input_stream (void)
{
  if (istream_type == ISTREAM_FILE)
    {
      if (cpp_pipe != NULL)
	fclose (cpp_pipe);

      if (cpp_temp_file != NULL)
	{
	  int errno_save = errno;

	  unlink (cpp_temp_file);
	  errno = errno_save;
	  free (cpp_temp_file);
	}
    }
  else
    {
      if (cpp_pipe != NULL)
	pclose (cpp_pipe);
    }

  /* Since this is also run via xatexit, safeguard.  */
  cpp_pipe = NULL;
  cpp_temp_file = NULL;
}