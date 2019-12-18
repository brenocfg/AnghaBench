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
 int /*<<< orphan*/  GET_UNSIGNED ; 
 scalar_t__ SIZEOF_LINETBL_DELTA ; 
 scalar_t__ SIZEOF_LINETBL_LENGTH ; 
 scalar_t__ SIZEOF_LINETBL_LINENO ; 
 scalar_t__ SIZEOF_LINETBL_STMT ; 
 scalar_t__ TARGET_FT_POINTER_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ baseaddr ; 
 int /*<<< orphan*/  current_objfile ; 
 int /*<<< orphan*/  current_subfile ; 
 int /*<<< orphan*/  objfile ; 
 int /*<<< orphan*/  record_line (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned long target_to_host (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
decode_line_numbers (char *linetable)
{
  char *tblscan;
  char *tblend;
  unsigned long length;
  unsigned long base;
  unsigned long line;
  unsigned long pc;

  if (linetable != NULL)
    {
      tblscan = tblend = linetable;
      length = target_to_host (tblscan, SIZEOF_LINETBL_LENGTH, GET_UNSIGNED,
			       current_objfile);
      tblscan += SIZEOF_LINETBL_LENGTH;
      tblend += length;
      base = target_to_host (tblscan, TARGET_FT_POINTER_SIZE (objfile),
			     GET_UNSIGNED, current_objfile);
      tblscan += TARGET_FT_POINTER_SIZE (objfile);
      base += baseaddr;
      while (tblscan < tblend)
	{
	  line = target_to_host (tblscan, SIZEOF_LINETBL_LINENO, GET_UNSIGNED,
				 current_objfile);
	  tblscan += SIZEOF_LINETBL_LINENO + SIZEOF_LINETBL_STMT;
	  pc = target_to_host (tblscan, SIZEOF_LINETBL_DELTA, GET_UNSIGNED,
			       current_objfile);
	  tblscan += SIZEOF_LINETBL_DELTA;
	  pc += base;
	  if (line != 0)
	    {
	      record_line (current_subfile, line, pc);
	    }
	}
    }
}