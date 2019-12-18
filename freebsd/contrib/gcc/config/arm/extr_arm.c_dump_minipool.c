#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_6__ {scalar_t__ address; } ;
struct TYPE_5__ {scalar_t__ refcount; int fix_size; struct TYPE_5__* next; int /*<<< orphan*/  value; scalar_t__ offset; scalar_t__ max_address; scalar_t__ min_address; } ;
typedef  TYPE_1__ Mnode ;

/* Variables and functions */
 scalar_t__ ARM_DOUBLEWORD_ALIGN ; 
 int INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_print_value (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  emit_barrier_after (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,unsigned int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  fputc (char,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_align_4 () ; 
 int /*<<< orphan*/  gen_align_8 () ; 
 int /*<<< orphan*/  gen_consttable_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_consttable_2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_consttable_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_consttable_8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_consttable_end () ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 TYPE_3__* minipool_barrier ; 
 TYPE_1__* minipool_vector_head ; 
 int /*<<< orphan*/  minipool_vector_label ; 
 int /*<<< orphan*/ * minipool_vector_tail ; 

__attribute__((used)) static void
dump_minipool (rtx scan)
{
  Mnode * mp;
  Mnode * nmp;
  int align64 = 0;

  if (ARM_DOUBLEWORD_ALIGN)
    for (mp = minipool_vector_head; mp != NULL; mp = mp->next)
      if (mp->refcount > 0 && mp->fix_size == 8)
	{
	  align64 = 1;
	  break;
	}

  if (dump_file)
    fprintf (dump_file,
	     ";; Emitting minipool after insn %u; address %ld; align %d (bytes)\n",
	     INSN_UID (scan), (unsigned long) minipool_barrier->address, align64 ? 8 : 4);

  scan = emit_label_after (gen_label_rtx (), scan);
  scan = emit_insn_after (align64 ? gen_align_8 () : gen_align_4 (), scan);
  scan = emit_label_after (minipool_vector_label, scan);

  for (mp = minipool_vector_head; mp != NULL; mp = nmp)
    {
      if (mp->refcount > 0)
	{
	  if (dump_file)
	    {
	      fprintf (dump_file,
		       ";;  Offset %u, min %ld, max %ld ",
		       (unsigned) mp->offset, (unsigned long) mp->min_address,
		       (unsigned long) mp->max_address);
	      arm_print_value (dump_file, mp->value);
	      fputc ('\n', dump_file);
	    }

	  switch (mp->fix_size)
	    {
#ifdef HAVE_consttable_1
	    case 1:
	      scan = emit_insn_after (gen_consttable_1 (mp->value), scan);
	      break;

#endif
#ifdef HAVE_consttable_2
	    case 2:
	      scan = emit_insn_after (gen_consttable_2 (mp->value), scan);
	      break;

#endif
#ifdef HAVE_consttable_4
	    case 4:
	      scan = emit_insn_after (gen_consttable_4 (mp->value), scan);
	      break;

#endif
#ifdef HAVE_consttable_8
	    case 8:
	      scan = emit_insn_after (gen_consttable_8 (mp->value), scan);
	      break;

#endif
	    default:
	      gcc_unreachable ();
	    }
	}

      nmp = mp->next;
      free (mp);
    }

  minipool_vector_head = minipool_vector_tail = NULL;
  scan = emit_insn_after (gen_consttable_end (), scan);
  scan = emit_barrier_after (scan);
}