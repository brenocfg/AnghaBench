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
struct ui_file {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  error_stream (struct ui_file*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fprintf_unfiltered (struct ui_file*,char*) ; 
 int /*<<< orphan*/  make_cleanup_ui_file_delete (struct ui_file*) ; 
 struct ui_file* mem_fileopen () ; 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,struct ui_file*) ; 
 int /*<<< orphan*/  safe_strerror (int) ; 

void
memory_error (int status, CORE_ADDR memaddr)
{
  struct ui_file *tmp_stream = mem_fileopen ();
  make_cleanup_ui_file_delete (tmp_stream);

  if (status == EIO)
    {
      /* Actually, address between memaddr and memaddr + len
         was out of bounds. */
      fprintf_unfiltered (tmp_stream, "Cannot access memory at address ");
      print_address_numeric (memaddr, 1, tmp_stream);
    }
  else
    {
      fprintf_filtered (tmp_stream, "Error accessing memory address ");
      print_address_numeric (memaddr, 1, tmp_stream);
      fprintf_filtered (tmp_stream, ": %s.",
		       safe_strerror (status));
    }

  error_stream (tmp_stream);
}