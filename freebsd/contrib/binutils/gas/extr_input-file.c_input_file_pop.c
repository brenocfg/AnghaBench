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
struct saved_file {int /*<<< orphan*/  app_save; scalar_t__ preprocess; int /*<<< orphan*/  file_name; int /*<<< orphan*/  f_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  app_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_in ; 
 int /*<<< orphan*/  file_name ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_file_end () ; 
 scalar_t__ preprocess ; 

void
input_file_pop (char *arg)
{
  register struct saved_file *saved = (struct saved_file *) arg;

  input_file_end ();		/* Close out old file.  */

  f_in = saved->f_in;
  file_name = saved->file_name;
  preprocess = saved->preprocess;
  if (preprocess)
    app_pop (saved->app_save);

  free (arg);
}