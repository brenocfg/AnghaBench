#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct internal_syment {int n_sclass; int /*<<< orphan*/  n_value; int /*<<< orphan*/  n_scnum; } ;
struct coff_visible {int type; } ;
typedef  enum coff_vis_type { ____Placeholder_coff_vis_type } coff_vis_type ;
struct TYPE_3__ {struct internal_syment syment; } ;
struct TYPE_4__ {TYPE_1__ u; } ;

/* Variables and functions */
#define  C_ARG 143 
#define  C_AUTO 142 
#define  C_AUTOARG 141 
#define  C_ENTAG 140 
#define  C_EXT 139 
#define  C_FIELD 138 
#define  C_LABEL 137 
#define  C_MOE 136 
#define  C_MOS 135 
#define  C_MOU 134 
#define  C_REG 133 
#define  C_REGPARM 132 
#define  C_STAT 131 
#define  C_STRTAG 130 
#define  C_TPDEF 129 
#define  C_UNTAG 128 
 int /*<<< orphan*/  N_UNDEF ; 
 int /*<<< orphan*/  abort () ; 
 int coff_vis_auto ; 
 int coff_vis_autoparam ; 
 int coff_vis_common ; 
 int coff_vis_ext_def ; 
 int coff_vis_ext_ref ; 
 int coff_vis_int_def ; 
 int coff_vis_member_of_enum ; 
 int coff_vis_member_of_struct ; 
 int coff_vis_register ; 
 int coff_vis_regparam ; 
 int coff_vis_tag ; 
 TYPE_2__* rawsyms ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static struct coff_visible *
do_visible (int i)
{
  struct internal_syment *sym = &rawsyms[i].u.syment;
  struct coff_visible *visible =
    (struct coff_visible *) (xmalloc (sizeof (struct coff_visible)));
  enum coff_vis_type t;
  switch (sym->n_sclass)
    {
    case C_MOS:
    case C_MOU:
    case C_FIELD:
      t = coff_vis_member_of_struct;
      break;
    case C_MOE:
      t = coff_vis_member_of_enum;
      break;

    case C_REGPARM:
      t = coff_vis_regparam;
      break;

    case C_REG:
      t = coff_vis_register;
      break;
    case C_STRTAG:
    case C_UNTAG:
    case C_ENTAG:
    case C_TPDEF:
      t = coff_vis_tag;
      break;
    case C_AUTOARG:
    case C_ARG:
      t = coff_vis_autoparam;
      break;
    case C_AUTO:


      t = coff_vis_auto;
      break;
    case C_LABEL:
    case C_STAT:
      t = coff_vis_int_def;
      break;
    case C_EXT:
      if (sym->n_scnum == N_UNDEF)
	{
	  if (sym->n_value)
	    t = coff_vis_common;
	  else
	    t = coff_vis_ext_ref;
	}
      else
	t = coff_vis_ext_def;
      break;
    default:
      abort ();
      break;

    }
  visible->type = t;
  return visible;
}