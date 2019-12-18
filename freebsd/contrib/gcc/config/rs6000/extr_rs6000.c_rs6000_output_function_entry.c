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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  ABI_AIX 130 
#define  ABI_DARWIN 129 
#define  ABI_V4 128 
 int /*<<< orphan*/  ASM_OUTPUT_INTERNAL_LABEL_PREFIX (int /*<<< orphan*/ *,char*) ; 
 int DEFAULT_ABI ; 
 int /*<<< orphan*/  DOT_SYMBOLS ; 
 int /*<<< orphan*/  RS6000_OUTPUT_BASENAME (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ TARGET_AIX ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

void
rs6000_output_function_entry (FILE *file, const char *fname)
{
  if (fname[0] != '.')
    {
      switch (DEFAULT_ABI)
	{
	default:
	  gcc_unreachable ();

	case ABI_AIX:
	  if (DOT_SYMBOLS)
	    putc ('.', file);
	  else
	    ASM_OUTPUT_INTERNAL_LABEL_PREFIX (file, "L.");
	  break;

	case ABI_V4:
	case ABI_DARWIN:
	  break;
	}
    }
  if (TARGET_AIX)
    RS6000_OUTPUT_BASENAME (file, fname);
  else
    assemble_name (file, fname);
}