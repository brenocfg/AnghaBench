#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  flags ;
typedef  int bfd_vma ;
struct TYPE_4__ {int d_val; int d_ptr; } ;
struct TYPE_5__ {int d_tag; TYPE_1__ d_un; } ;
typedef  TYPE_2__ Elf_Internal_Dyn ;

/* Variables and functions */
#define  DT_HP_BIND_DEPTH_FIRST 145 
#define  DT_HP_BIND_NONFATAL 144 
#define  DT_HP_BIND_NOW 143 
#define  DT_HP_BIND_RESTRICTED 142 
#define  DT_HP_BIND_SYMBOLIC 141 
#define  DT_HP_BIND_VERBOSE 140 
#define  DT_HP_DEBUG_CALLBACK 139 
#define  DT_HP_DEBUG_CALLBACK_BOR 138 
#define  DT_HP_DEBUG_PRIVATE 137 
#define  DT_HP_DLD_FLAGS 136 
#define  DT_HP_GROUP 135 
#define  DT_HP_GST 134 
#define  DT_HP_MERGE_SHLIB_SEG 133 
#define  DT_HP_NODELETE 132 
#define  DT_HP_NO_ENVVAR 131 
#define  DT_HP_PROTECT_LINKAGE_TABLE 130 
#define  DT_HP_RPATH_FIRST 129 
#define  DT_HP_SHLIB_FIXED 128 
 int /*<<< orphan*/  HEX ; 
 int /*<<< orphan*/  PREFIX_HEX ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_vma (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
dynamic_section_parisc_val (Elf_Internal_Dyn *entry)
{
  switch (entry->d_tag)
    {
    case DT_HP_DLD_FLAGS:
      {
	static struct
	{
	  long int bit;
	  const char *str;
	}
	flags[] =
	{
	  { DT_HP_DEBUG_PRIVATE, "HP_DEBUG_PRIVATE" },
	  { DT_HP_DEBUG_CALLBACK, "HP_DEBUG_CALLBACK" },
	  { DT_HP_DEBUG_CALLBACK_BOR, "HP_DEBUG_CALLBACK_BOR" },
	  { DT_HP_NO_ENVVAR, "HP_NO_ENVVAR" },
	  { DT_HP_BIND_NOW, "HP_BIND_NOW" },
	  { DT_HP_BIND_NONFATAL, "HP_BIND_NONFATAL" },
	  { DT_HP_BIND_VERBOSE, "HP_BIND_VERBOSE" },
	  { DT_HP_BIND_RESTRICTED, "HP_BIND_RESTRICTED" },
	  { DT_HP_BIND_SYMBOLIC, "HP_BIND_SYMBOLIC" },
	  { DT_HP_RPATH_FIRST, "HP_RPATH_FIRST" },
	  { DT_HP_BIND_DEPTH_FIRST, "HP_BIND_DEPTH_FIRST" },
	  { DT_HP_GST, "HP_GST" },
	  { DT_HP_SHLIB_FIXED, "HP_SHLIB_FIXED" },
	  { DT_HP_MERGE_SHLIB_SEG, "HP_MERGE_SHLIB_SEG" },
	  { DT_HP_NODELETE, "HP_NODELETE" },
	  { DT_HP_GROUP, "HP_GROUP" },
	  { DT_HP_PROTECT_LINKAGE_TABLE, "HP_PROTECT_LINKAGE_TABLE" }
	};
	int first = 1;
	size_t cnt;
	bfd_vma val = entry->d_un.d_val;

	for (cnt = 0; cnt < sizeof (flags) / sizeof (flags[0]); ++cnt)
	  if (val & flags[cnt].bit)
	    {
	      if (! first)
		putchar (' ');
	      fputs (flags[cnt].str, stdout);
	      first = 0;
	      val ^= flags[cnt].bit;
	    }

	if (val != 0 || first)
	  {
	    if (! first)
	      putchar (' ');
	    print_vma (val, HEX);
	  }
      }
      break;

    default:
      print_vma (entry->d_un.d_ptr, PREFIX_HEX);
      break;
    }
  putchar ('\n');
}