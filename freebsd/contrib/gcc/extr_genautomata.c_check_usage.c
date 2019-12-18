#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* decl_t ;
struct TYPE_10__ {int /*<<< orphan*/  name; int /*<<< orphan*/  reserv_is_used; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; int /*<<< orphan*/  unit_is_used; } ;
struct TYPE_8__ {int decls_num; TYPE_1__** decls; } ;
struct TYPE_7__ {scalar_t__ mode; } ;

/* Variables and functions */
 TYPE_5__* DECL_RESERV (TYPE_1__*) ; 
 TYPE_3__* DECL_UNIT (TYPE_1__*) ; 
 TYPE_2__* description ; 
 scalar_t__ dm_reserv ; 
 scalar_t__ dm_unit ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_flag ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_usage (void)
{
  decl_t decl;
  int i;

  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_unit && !DECL_UNIT (decl)->unit_is_used)
	{
	  if (!w_flag)
	    error ("unit `%s' is not used", DECL_UNIT (decl)->name);
	  else
	    warning (0, "unit `%s' is not used", DECL_UNIT (decl)->name);
	}
      else if (decl->mode == dm_reserv && !DECL_RESERV (decl)->reserv_is_used)
	{
	  if (!w_flag)
	    error ("reservation `%s' is not used", DECL_RESERV (decl)->name);
	  else
	    warning (0, "reservation `%s' is not used", DECL_RESERV (decl)->name);
	}
    }
}