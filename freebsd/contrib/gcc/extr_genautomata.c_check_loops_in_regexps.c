#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* decl_t ;
struct TYPE_8__ {int loop_pass_num; int /*<<< orphan*/  name; int /*<<< orphan*/  regexp; } ;
struct TYPE_7__ {int decls_num; TYPE_1__** decls; } ;
struct TYPE_6__ {scalar_t__ mode; } ;

/* Variables and functions */
 TYPE_4__* DECL_RESERV (TYPE_1__*) ; 
 int curr_loop_pass_num ; 
 TYPE_3__* description ; 
 scalar_t__ dm_reserv ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ loop_in_regexp (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
check_loops_in_regexps (void)
{
  decl_t decl;
  int i;

  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_reserv)
	DECL_RESERV (decl)->loop_pass_num = 0;
    }
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      curr_loop_pass_num = i;

      if (decl->mode == dm_reserv)
	  {
	    DECL_RESERV (decl)->loop_pass_num = curr_loop_pass_num;
	    if (loop_in_regexp (DECL_RESERV (decl)->regexp, decl))
	      {
		gcc_assert (DECL_RESERV (decl)->regexp);
		error ("cycle in definition of reservation `%s'",
		       DECL_RESERV (decl)->name);
	      }
	  }
    }
}