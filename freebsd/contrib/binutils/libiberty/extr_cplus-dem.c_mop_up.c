#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct work_stuff {int dummy; } ;
struct TYPE_5__ {char* b; } ;
typedef  TYPE_1__ string ;

/* Variables and functions */
 int /*<<< orphan*/  delete_non_B_K_work_stuff (struct work_stuff*) ; 
 int /*<<< orphan*/  string_appendn (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  string_delete (TYPE_1__*) ; 

__attribute__((used)) static char *
mop_up (struct work_stuff *work, string *declp, int success)
{
  char *demangled = NULL;

  delete_non_B_K_work_stuff (work);

  /* If demangling was successful, ensure that the demangled string is null
     terminated and return it.  Otherwise, free the demangling decl.  */

  if (!success)
    {
      string_delete (declp);
    }
  else
    {
      string_appendn (declp, "", 1);
      demangled = declp->b;
    }
  return (demangled);
}