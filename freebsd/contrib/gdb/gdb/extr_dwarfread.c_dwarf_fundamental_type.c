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
struct objfile {int dummy; } ;
struct TYPE_2__ {struct type* (* la_fund_type ) (struct objfile*,int) ;} ;

/* Variables and functions */
 int FT_NUM_MEMBERS ; 
 TYPE_1__* cu_language_defn ; 
 int /*<<< orphan*/  error (char*,int) ; 
 struct type** ftypes ; 
 struct type* stub1 (struct objfile*,int) ; 

__attribute__((used)) static struct type *
dwarf_fundamental_type (struct objfile *objfile, int typeid)
{
  if (typeid < 0 || typeid >= FT_NUM_MEMBERS)
    {
      error ("internal error - invalid fundamental type id %d", typeid);
    }

  /* Look for this particular type in the fundamental type vector.  If one is
     not found, create and install one appropriate for the current language
     and the current target machine. */

  if (ftypes[typeid] == NULL)
    {
      ftypes[typeid] = cu_language_defn->la_fund_type (objfile, typeid);
    }

  return (ftypes[typeid]);
}