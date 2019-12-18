#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct pta   TYPE_1__ ;

/* Type definitions */
typedef  enum processor_type { ____Placeholder_processor_type } processor_type ;
struct pta {char const* name; int processor; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__ const*) ; 
#define  OPT_mfixed_range_ 132 
#define  OPT_mtls_size_ 131 
#define  OPT_mtune_ 130 
#define  PROCESSOR_ITANIUM 129 
#define  PROCESSOR_ITANIUM2 128 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  fix_range (char const*) ; 
 int ia64_tune ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static bool
ia64_handle_option (size_t code, const char *arg, int value)
{
  switch (code)
    {
    case OPT_mfixed_range_:
      fix_range (arg);
      return true;

    case OPT_mtls_size_:
      if (value != 14 && value != 22 && value != 64)
	error ("bad value %<%s%> for -mtls-size= switch", arg);
      return true;

    case OPT_mtune_:
      {
	static struct pta
	  {
	    const char *name;		/* processor name or nickname.  */
	    enum processor_type processor;
	  }
	const processor_alias_table[] =
	  {
	    {"itanium", PROCESSOR_ITANIUM},
	    {"itanium1", PROCESSOR_ITANIUM},
	    {"merced", PROCESSOR_ITANIUM},
	    {"itanium2", PROCESSOR_ITANIUM2},
	    {"mckinley", PROCESSOR_ITANIUM2},
	  };
	int const pta_size = ARRAY_SIZE (processor_alias_table);
	int i;

	for (i = 0; i < pta_size; i++)
	  if (!strcmp (arg, processor_alias_table[i].name))
	    {
	      ia64_tune = processor_alias_table[i].processor;
	      break;
	    }
	if (i == pta_size)
	  error ("bad value %<%s%> for -mtune= switch", arg);
	return true;
      }

    default:
      return true;
    }
}