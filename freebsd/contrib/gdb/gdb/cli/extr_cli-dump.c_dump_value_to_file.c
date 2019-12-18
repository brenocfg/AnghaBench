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
struct value {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 scalar_t__ VALUE_LVAL (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  dump_bfd_file (char*,char*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_binary_file (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  null_cleanup ; 
 struct value* parse_and_eval (char*) ; 
 char* scan_filename_with_cleanup (char**,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
dump_value_to_file (char *cmd, char *mode, char *file_format)
{
  struct cleanup *old_cleanups = make_cleanup (null_cleanup, NULL);
  struct value *val;
  char *filename;

  /* Open the file.  */
  filename = scan_filename_with_cleanup (&cmd, NULL);

  /* Find the value.  */
  if (cmd == NULL || *cmd == '\0')
    error ("No value to %s.", *mode == 'a' ? "append" : "dump");
  val = parse_and_eval (cmd);
  if (val == NULL)
    error ("Invalid expression.");

  /* Have everything.  Open/write the data.  */
  if (file_format == NULL || strcmp (file_format, "binary") == 0)
    {
      dump_binary_file (filename, mode, VALUE_CONTENTS (val), 
			TYPE_LENGTH (VALUE_TYPE (val)));
    }
  else
    {
      CORE_ADDR vaddr;

      if (VALUE_LVAL (val))
	{
	  vaddr = VALUE_ADDRESS (val);
	}
      else
	{
	  vaddr = 0;
	  warning ("value is not an lval: address assumed to be zero");
	}

      dump_bfd_file (filename, mode, file_format, vaddr, 
		     VALUE_CONTENTS (val), 
		     TYPE_LENGTH (VALUE_TYPE (val)));
    }

  do_cleanups (old_cleanups);
}