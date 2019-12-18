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
 int /*<<< orphan*/  buffer_limit ; 
 int /*<<< orphan*/  input_line_pointer ; 
 int /*<<< orphan*/  input_scrub_include_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_scrub_next_buffer (int /*<<< orphan*/ *) ; 

void
input_scrub_insert_file (char *path)
{
  input_scrub_include_file (path, input_line_pointer);
  buffer_limit = input_scrub_next_buffer (&input_line_pointer);
}