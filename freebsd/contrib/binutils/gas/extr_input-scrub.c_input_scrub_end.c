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
 scalar_t__ buffer_start ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  input_file_end () ; 

void
input_scrub_end (void)
{
  if (buffer_start)
    {
      free (buffer_start);
      buffer_start = 0;
      input_file_end ();
    }
}