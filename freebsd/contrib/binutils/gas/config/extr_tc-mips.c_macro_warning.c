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
typedef  int relax_substateT ;

/* Variables and functions */
 int RELAX_DELAY_SLOT ; 
 int RELAX_NOMACRO ; 
 char const* _ (char*) ; 

__attribute__((used)) static const char *
macro_warning (relax_substateT subtype)
{
  if (subtype & RELAX_DELAY_SLOT)
    return _("Macro instruction expanded into multiple instructions"
	     " in a branch delay slot");
  else if (subtype & RELAX_NOMACRO)
    return _("Macro instruction expanded into multiple instructions");
  else
    return 0;
}