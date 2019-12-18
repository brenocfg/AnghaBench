#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ origin; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ directive ;
struct TYPE_10__ {int /*<<< orphan*/  skipping; } ;
struct TYPE_12__ {TYPE_1__ state; } ;
typedef  TYPE_3__ cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_PEDWARN ; 
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 scalar_t__ CPP_PEDANTIC (TYPE_3__*) ; 
 scalar_t__ CPP_WTRADITIONAL (TYPE_3__*) ; 
 scalar_t__ EXTENSION ; 
 scalar_t__ KANDR ; 
 size_t T_ELIF ; 
 int /*<<< orphan*/  cpp_error (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__ const* dtable ; 

__attribute__((used)) static void
directive_diagnostics (cpp_reader *pfile, const directive *dir, int indented)
{
  /* Issue -pedantic warnings for extensions.  */
  if (CPP_PEDANTIC (pfile)
      && ! pfile->state.skipping
      && dir->origin == EXTENSION)
    cpp_error (pfile, CPP_DL_PEDWARN, "#%s is a GCC extension", dir->name);

  /* Traditionally, a directive is ignored unless its # is in
     column 1.  Therefore in code intended to work with K+R
     compilers, directives added by C89 must have their #
     indented, and directives present in traditional C must not.
     This is true even of directives in skipped conditional
     blocks.  #elif cannot be used at all.  */
  if (CPP_WTRADITIONAL (pfile))
    {
      if (dir == &dtable[T_ELIF])
	cpp_error (pfile, CPP_DL_WARNING,
		   "suggest not using #elif in traditional C");
      else if (indented && dir->origin == KANDR)
	cpp_error (pfile, CPP_DL_WARNING,
		   "traditional C ignores #%s with the # indented",
		   dir->name);
      else if (!indented && dir->origin != KANDR)
	cpp_error (pfile, CPP_DL_WARNING,
		   "suggest hiding #%s from traditional C with an indented #",
		   dir->name);
    }
}