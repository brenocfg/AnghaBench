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
struct cleanup {int dummy; } ;
typedef  scalar_t__ ULONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  dump_bfd_file (char*,char*,char*,scalar_t__,void*,scalar_t__) ; 
 int /*<<< orphan*/  dump_binary_file (char*,char*,void*,scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  null_cleanup ; 
 scalar_t__ parse_and_eval_address (char*) ; 
 char* scan_expression_with_cleanup (char**,int /*<<< orphan*/ *) ; 
 char* scan_filename_with_cleanup (char**,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  target_read_memory (scalar_t__,void*,scalar_t__) ; 
 int /*<<< orphan*/  xfree ; 
 void* xmalloc (scalar_t__) ; 

__attribute__((used)) static void
dump_memory_to_file (char *cmd, char *mode, char *file_format)
{
  struct cleanup *old_cleanups = make_cleanup (null_cleanup, NULL);
  CORE_ADDR lo;
  CORE_ADDR hi;
  ULONGEST count;
  char *filename;
  void *buf;
  char *lo_exp;
  char *hi_exp;
  int len;

  /* Open the file.  */
  filename = scan_filename_with_cleanup (&cmd, NULL);

  /* Find the low address.  */
  if (cmd == NULL || *cmd == '\0')
    error ("Missing start address.");
  lo_exp = scan_expression_with_cleanup (&cmd, NULL);

  /* Find the second address - rest of line.  */
  if (cmd == NULL || *cmd == '\0')
    error ("Missing stop address.");
  hi_exp = cmd;

  lo = parse_and_eval_address (lo_exp);
  hi = parse_and_eval_address (hi_exp);
  if (hi <= lo)
    error ("Invalid memory address range (start >= end).");
  count = hi - lo;

  /* FIXME: Should use read_memory_partial() and a magic blocking
     value.  */
  buf = xmalloc (count);
  make_cleanup (xfree, buf);
  target_read_memory (lo, buf, count);
  
  /* Have everything.  Open/write the data.  */
  if (file_format == NULL || strcmp (file_format, "binary") == 0)
    {
      dump_binary_file (filename, mode, buf, count);
    }
  else
    {
      dump_bfd_file (filename, mode, file_format, lo, buf, count);
    }

  do_cleanups (old_cleanups);
}