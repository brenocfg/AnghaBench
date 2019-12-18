#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ line; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ expanded_location ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SOURCE_LOCATION (int /*<<< orphan*/ ) ; 
 scalar_t__ GCOV_NOTE_MAGIC ; 
 int /*<<< orphan*/  GCOV_TAG_FUNCTION ; 
 scalar_t__ GCOV_VERSION ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbg_file_name ; 
 int bbg_file_opened ; 
 int bbg_function_announced ; 
 scalar_t__ compute_checksum () ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ current_function_funcdef_no ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ expand_location (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcov_is_error () ; 
 int /*<<< orphan*/  gcov_open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcov_write_length (unsigned long) ; 
 int /*<<< orphan*/  gcov_write_string (int /*<<< orphan*/ ) ; 
 unsigned long gcov_write_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcov_write_unsigned (scalar_t__) ; 
 scalar_t__ local_tick ; 
 scalar_t__ no_coverage ; 

int
coverage_begin_output (void)
{
  if (no_coverage)
    return 0;

  if (!bbg_function_announced)
    {
      expanded_location xloc
	= expand_location (DECL_SOURCE_LOCATION (current_function_decl));
      unsigned long offset;

      if (!bbg_file_opened)
	{
	  if (!gcov_open (bbg_file_name, -1))
	    error ("cannot open %s", bbg_file_name);
	  else
	    {
	      gcov_write_unsigned (GCOV_NOTE_MAGIC);
	      gcov_write_unsigned (GCOV_VERSION);
	      gcov_write_unsigned (local_tick);
	    }
	  bbg_file_opened = 1;
	}

      /* Announce function */
      offset = gcov_write_tag (GCOV_TAG_FUNCTION);
      gcov_write_unsigned (current_function_funcdef_no + 1);
      gcov_write_unsigned (compute_checksum ());
      gcov_write_string (IDENTIFIER_POINTER
			 (DECL_ASSEMBLER_NAME (current_function_decl)));
      gcov_write_string (xloc.file);
      gcov_write_unsigned (xloc.line);
      gcov_write_length (offset);

      bbg_function_announced = 1;
    }
  return !gcov_is_error ();
}