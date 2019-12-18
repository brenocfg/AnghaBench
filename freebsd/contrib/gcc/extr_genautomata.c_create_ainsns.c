#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ainsn {int dummy; } ;
typedef  TYPE_1__* decl_t ;
typedef  TYPE_2__* ainsn_t ;
struct TYPE_9__ {int decls_num; TYPE_1__** decls; } ;
struct TYPE_8__ {struct TYPE_8__* next_ainsn; int /*<<< orphan*/  important_p; int /*<<< orphan*/  insn_reserv_decl; } ;
struct TYPE_7__ {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_INSN_RESERV (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* create_node (int) ; 
 TYPE_3__* description ; 
 scalar_t__ dm_insn_reserv ; 

__attribute__((used)) static ainsn_t
create_ainsns (void)
{
  decl_t decl;
  ainsn_t first_ainsn;
  ainsn_t curr_ainsn;
  ainsn_t prev_ainsn;
  int i;

  first_ainsn = NULL;
  prev_ainsn = NULL;
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_insn_reserv)
	{
	  curr_ainsn = create_node (sizeof (struct ainsn));
	  curr_ainsn->insn_reserv_decl = DECL_INSN_RESERV (decl);
	  curr_ainsn->important_p = FALSE;
	  curr_ainsn->next_ainsn = NULL;
	  if (prev_ainsn == NULL)
	    first_ainsn = curr_ainsn;
	  else
	    prev_ainsn->next_ainsn = curr_ainsn;
	  prev_ainsn = curr_ainsn;
	}
    }
  return first_ainsn;
}