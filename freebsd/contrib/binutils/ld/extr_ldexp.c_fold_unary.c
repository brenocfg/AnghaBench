#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int node_code; } ;
struct TYPE_8__ {int /*<<< orphan*/  child; } ;
struct TYPE_12__ {TYPE_2__ type; TYPE_1__ unary; } ;
typedef  TYPE_5__ etree_type ;
struct TYPE_11__ {int value; void* valid_p; } ;
struct TYPE_10__ {int end; int /*<<< orphan*/  phase; } ;
struct TYPE_13__ {TYPE_4__ result; TYPE_3__ dataseg; int /*<<< orphan*/  phase; int /*<<< orphan*/  section; int /*<<< orphan*/  dot; } ;

/* Variables and functions */
#define  ABSOLUTE 131 
#define  ALIGN_K 130 
#define  DATA_SEGMENT_END 129 
 int /*<<< orphan*/  FAIL () ; 
 void* FALSE ; 
#define  NEXT 128 
 int align_n (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_abs_section_ptr ; 
 int /*<<< orphan*/  exp_dataseg_adjust ; 
 int /*<<< orphan*/  exp_dataseg_align_seen ; 
 int /*<<< orphan*/  exp_dataseg_end_seen ; 
 int /*<<< orphan*/  exp_dataseg_relro_adjust ; 
 int /*<<< orphan*/  exp_dataseg_relro_seen ; 
 int /*<<< orphan*/  exp_fold_tree_1 (int /*<<< orphan*/ ) ; 
 TYPE_7__ expld ; 
 int /*<<< orphan*/  lang_final_phase_enum ; 
 int /*<<< orphan*/  lang_first_phase_enum ; 
 int /*<<< orphan*/  make_abs () ; 
 int /*<<< orphan*/  new_rel_from_abs (int) ; 

__attribute__((used)) static void
fold_unary (etree_type *tree)
{
  exp_fold_tree_1 (tree->unary.child);
  if (expld.result.valid_p)
    {
      switch (tree->type.node_code)
	{
	case ALIGN_K:
	  if (expld.phase != lang_first_phase_enum)
	    new_rel_from_abs (align_n (expld.dot, expld.result.value));
	  else
	    expld.result.valid_p = FALSE;
	  break;

	case ABSOLUTE:
	  make_abs ();
	  break;

	case '~':
	  make_abs ();
	  expld.result.value = ~expld.result.value;
	  break;

	case '!':
	  make_abs ();
	  expld.result.value = !expld.result.value;
	  break;

	case '-':
	  make_abs ();
	  expld.result.value = -expld.result.value;
	  break;

	case NEXT:
	  /* Return next place aligned to value.  */
	  if (expld.phase != lang_first_phase_enum)
	    {
	      make_abs ();
	      expld.result.value = align_n (expld.dot, expld.result.value);
	    }
	  else
	    expld.result.valid_p = FALSE;
	  break;

	case DATA_SEGMENT_END:
	  if (expld.phase != lang_first_phase_enum
	      && expld.section == bfd_abs_section_ptr
	      && (expld.dataseg.phase == exp_dataseg_align_seen
		  || expld.dataseg.phase == exp_dataseg_relro_seen
		  || expld.dataseg.phase == exp_dataseg_adjust
		  || expld.dataseg.phase == exp_dataseg_relro_adjust
		  || expld.phase == lang_final_phase_enum))
	    {
	      if (expld.dataseg.phase == exp_dataseg_align_seen
		  || expld.dataseg.phase == exp_dataseg_relro_seen)
		{
		  expld.dataseg.phase = exp_dataseg_end_seen;
		  expld.dataseg.end = expld.result.value;
		}
	    }
	  else
	    expld.result.valid_p = FALSE;
	  break;

	default:
	  FAIL ();
	  break;
	}
    }
}