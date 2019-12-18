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
struct type {int dummy; } ;
struct objfile {char* name; } ;
struct dwarf2_cu {struct type** ftypes; TYPE_1__* language_defn; } ;
struct TYPE_2__ {struct type* (* la_fund_type ) (struct objfile*,int) ;} ;

/* Variables and functions */
 int FT_NUM_MEMBERS ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 struct type* stub1 (struct objfile*,int) ; 

__attribute__((used)) static struct type *
dwarf2_fundamental_type (struct objfile *objfile, int typeid,
			 struct dwarf2_cu *cu)
{
  if (typeid < 0 || typeid >= FT_NUM_MEMBERS)
    {
      error ("Dwarf Error: internal error - invalid fundamental type id %d [in module %s]",
	     typeid, objfile->name);
    }

  /* Look for this particular type in the fundamental type vector.  If
     one is not found, create and install one appropriate for the
     current language and the current target machine. */

  if (cu->ftypes[typeid] == NULL)
    {
      cu->ftypes[typeid] = cu->language_defn->la_fund_type (objfile, typeid);
    }

  return (cu->ftypes[typeid]);
}