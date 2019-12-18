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
 char* input_scrub_new_file (char*) ; 
 int /*<<< orphan*/  input_scrub_push (char*) ; 
 int /*<<< orphan*/  next_saved_file ; 

char *
input_scrub_include_file (char *filename, char *position)
{
  next_saved_file = input_scrub_push (position);
  return input_scrub_new_file (filename);
}