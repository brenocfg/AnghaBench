#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct percent_op_match {int /*<<< orphan*/  str; int /*<<< orphan*/  reloc; } ;
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {scalar_t__ mips16; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct percent_op_match*) ; 
 int /*<<< orphan*/  BFD_RELOC_UNUSED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ISSPACE (char) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  as_bad (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_reloc_type_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct percent_op_match* mips16_percent_op ; 
 TYPE_1__ mips_opts ; 
 struct percent_op_match* mips_percent_op ; 
 int /*<<< orphan*/  stdoutput ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bfd_boolean
parse_relocation (char **str, bfd_reloc_code_real_type *reloc)
{
  const struct percent_op_match *percent_op;
  size_t limit, i;

  if (mips_opts.mips16)
    {
      percent_op = mips16_percent_op;
      limit = ARRAY_SIZE (mips16_percent_op);
    }
  else
    {
      percent_op = mips_percent_op;
      limit = ARRAY_SIZE (mips_percent_op);
    }

  for (i = 0; i < limit; i++)
    if (strncasecmp (*str, percent_op[i].str, strlen (percent_op[i].str)) == 0)
      {
	int len = strlen (percent_op[i].str);

	if (!ISSPACE ((*str)[len]) && (*str)[len] != '(')
	  continue;

	*str += strlen (percent_op[i].str);
	*reloc = percent_op[i].reloc;

	/* Check whether the output BFD supports this relocation.
	   If not, issue an error and fall back on something safe.  */
	if (!bfd_reloc_type_lookup (stdoutput, percent_op[i].reloc))
	  {
	    as_bad ("relocation %s isn't supported by the current ABI",
		    percent_op[i].str);
	    *reloc = BFD_RELOC_UNUSED;
	  }
	return TRUE;
      }
  return FALSE;
}