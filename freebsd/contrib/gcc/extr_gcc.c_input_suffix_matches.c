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
struct TYPE_2__ {scalar_t__ suffix; } ;

/* Variables and functions */
 TYPE_1__* input_file_compiler ; 
 char* input_suffix ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static inline bool
input_suffix_matches (const char *atom, const char *end_atom)
{
  /* We special case the semantics of {.s:...} and {.S:...} and their
     negative variants.  Instead of testing the input filename suffix,
     we test whether the input source file is an assembler file or an
     assembler-with-cpp file respectively.  This allows us to correctly
     handle the -x command line option.  */

  if (atom + 1 == end_atom
      && input_file_compiler
      && input_file_compiler->suffix)
    {
      if (*atom == 's')
	return !strcmp (input_file_compiler->suffix, "@assembler");
      if (*atom == 'S')
	return !strcmp (input_file_compiler->suffix, "@assembler-with-cpp");
    }

  return (input_suffix
	  && !strncmp (input_suffix, atom, end_atom - atom)
	  && input_suffix[end_atom - atom] == '\0');
}