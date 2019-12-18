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
 int AFTER_SIZE ; 
 char* AFTER_STRING ; 
 scalar_t__ BEFORE_SIZE ; 
 char* BEFORE_STRING ; 
 scalar_t__ buffer_length ; 
 int /*<<< orphan*/  buffer_start ; 
 int /*<<< orphan*/  do_scrub_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_m68k_mri ; 
 int /*<<< orphan*/  input_file_begin () ; 
 scalar_t__ input_file_buffer_size () ; 
 int /*<<< orphan*/  know (int) ; 
 char* logical_input_file ; 
 int logical_input_line ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * next_saved_file ; 
 int /*<<< orphan*/ * physical_input_file ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xmalloc (scalar_t__) ; 

void
input_scrub_begin (void)
{
  know (strlen (BEFORE_STRING) == BEFORE_SIZE);
  know (strlen (AFTER_STRING) == AFTER_SIZE
	|| (AFTER_STRING[0] == '\0' && AFTER_SIZE == 1));

  input_file_begin ();

  buffer_length = input_file_buffer_size ();

  buffer_start = xmalloc ((BEFORE_SIZE + buffer_length + buffer_length + AFTER_SIZE));
  memcpy (buffer_start, BEFORE_STRING, (int) BEFORE_SIZE);

  /* Line number things.  */
  logical_input_line = -1;
  logical_input_file = (char *) NULL;
  physical_input_file = NULL;	/* No file read yet.  */
  next_saved_file = NULL;	/* At EOF, don't pop to any other file */
  do_scrub_begin (flag_m68k_mri);
}