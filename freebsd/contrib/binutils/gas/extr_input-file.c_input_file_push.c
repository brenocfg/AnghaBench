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
 int /*<<< orphan*/  app_push () ; 
 int /*<<< orphan*/  f_in ; 
 int /*<<< orphan*/  file_name ; 
 int /*<<< orphan*/  input_file_begin () ; 
 scalar_t__ preprocess ; 
 scalar_t__ xmalloc (int) ; 

char *
input_file_push (void)
{
  register struct saved_file *saved;

  saved = (struct saved_file *) xmalloc (sizeof *saved);

  saved->f_in = f_in;
  saved->file_name = file_name;
  saved->preprocess = preprocess;
  if (preprocess)
    saved->app_save = app_push ();

  /* Initialize for new file.  */
  input_file_begin ();

  return (char *) saved;
}