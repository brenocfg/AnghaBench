#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_20__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_33__ {char** _n_nptr; } ;
struct internal_syment {int n_sclass; int /*<<< orphan*/  n_numaux; scalar_t__ n_value; scalar_t__ n_scnum; TYPE_4__ _n; } ;
struct coff_sfile {char* name; struct coff_sfile* next; TYPE_12__* scope; struct coff_isection* section; } ;
struct coff_ofile {scalar_t__ sections; scalar_t__ nsources; struct coff_sfile* source_tail; struct coff_sfile* source_head; scalar_t__ symbol_list_head; scalar_t__ symbol_list_tail; } ;
struct coff_isection {int dummy; } ;
struct TYPE_37__ {TYPE_12__* elements; } ;
struct TYPE_38__ {TYPE_8__ astructdef; } ;
struct TYPE_34__ {TYPE_12__* parameters; } ;
struct TYPE_35__ {TYPE_5__ function; } ;
struct TYPE_36__ {TYPE_6__ u; } ;
struct TYPE_31__ {TYPE_12__* code; } ;
struct TYPE_32__ {TYPE_2__ function; } ;
struct TYPE_30__ {int /*<<< orphan*/  section_count; } ;
struct TYPE_29__ {struct internal_syment syment; } ;
struct TYPE_21__ {TYPE_12__* elements; } ;
struct TYPE_22__ {TYPE_10__ aenumdef; } ;
struct TYPE_28__ {TYPE_11__ u; } ;
struct TYPE_27__ {TYPE_7__* type; } ;
struct TYPE_26__ {TYPE_3__ u; } ;
struct TYPE_25__ {TYPE_9__ u; } ;
struct TYPE_24__ {TYPE_1__ u; } ;
struct TYPE_23__ {scalar_t__ offset; int /*<<< orphan*/  size; scalar_t__ sec; } ;

/* Variables and functions */
#define  C_ARG 146 
#define  C_AUTO 145 
#define  C_BLOCK 144 
#define  C_ENTAG 143 
#define  C_EOS 142 
#define  C_EXT 141 
#define  C_FCN 140 
#define  C_FIELD 139 
#define  C_FILE 138 
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
 TYPE_20__* abfd ; 
 int /*<<< orphan*/  abort () ; 
 struct coff_sfile* cur_sfile ; 
 int do_define (int,TYPE_12__*) ; 
 int /*<<< orphan*/  do_sections_p1 (struct coff_ofile*) ; 
 int /*<<< orphan*/  do_sections_p2 (struct coff_ofile*) ; 
 TYPE_12__* file_scope ; 
 TYPE_17__* last_enum ; 
 TYPE_16__* last_function_symbol ; 
 TYPE_15__* last_function_type ; 
 TYPE_14__* last_struct ; 
 struct coff_ofile* ofile ; 
 int /*<<< orphan*/  pop_scope () ; 
 int /*<<< orphan*/  push_scope (int) ; 
 int rawcount ; 
 TYPE_13__* rawsyms ; 
 TYPE_12__* top_scope ; 
 scalar_t__ xcalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static
struct coff_ofile *
doit (void)
{
  int i;
  int infile = 0;
  struct coff_ofile *head =
    (struct coff_ofile *) xmalloc (sizeof (struct coff_ofile));
  ofile = head;
  head->source_head = 0;
  head->source_tail = 0;
  head->nsources = 0;
  head->symbol_list_tail = 0;
  head->symbol_list_head = 0;
  do_sections_p1 (head);
  push_scope (1);

  for (i = 0; i < rawcount;)
    {
      struct internal_syment *sym = &rawsyms[i].u.syment;
      switch (sym->n_sclass)
	{
	case C_FILE:
	  {
	    /* new source file announced */
	    struct coff_sfile *n =
	      (struct coff_sfile *) xmalloc (sizeof (struct coff_sfile));
	    n->section = (struct coff_isection *) xcalloc (sizeof (struct coff_isection), abfd->section_count + 1);
	    cur_sfile = n;
	    n->name = sym->_n._n_nptr[1];
	    n->next = 0;

	    if (infile)
	      {
		pop_scope ();
	      }
	    infile = 1;
	    push_scope (1);
	    file_scope = n->scope = top_scope;

	    if (head->source_tail)
	      head->source_tail->next = n;
	    else
	      head->source_head = n;
	    head->source_tail = n;
	    head->nsources++;
	    i += sym->n_numaux + 1;
	  }
	  break;
	case C_FCN:
	  {
	    char *name = sym->_n._n_nptr[1];
	    if (name[1] == 'b')
	      {
		/* Function start */
		push_scope (0);
		last_function_type->u.function.code = top_scope;
		top_scope->sec = ofile->sections + sym->n_scnum;
		top_scope->offset = sym->n_value;
	      }
	    else
	      {
		top_scope->size = sym->n_value - top_scope->offset + 1;
		pop_scope ();

	      }
	    i += sym->n_numaux + 1;
	  }
	  break;

	case C_BLOCK:
	  {
	    char *name = sym->_n._n_nptr[1];
	    if (name[1] == 'b')
	      {
		/* Block start */
		push_scope (1);
		top_scope->sec = ofile->sections + sym->n_scnum;
		top_scope->offset = sym->n_value;

	      }
	    else
	      {
		top_scope->size = sym->n_value - top_scope->offset + 1;
		pop_scope ();
	      }
	    i += sym->n_numaux + 1;
	  }
	  break;
	case C_REGPARM:
	case C_ARG:
	  i = do_define (i, last_function_symbol->type->u.function.parameters);
	  break;
	case C_MOS:
	case C_MOU:
	case C_FIELD:
	  i = do_define (i, last_struct->u.astructdef.elements);
	  break;
	case C_MOE:
	  i = do_define (i, last_enum->u.aenumdef.elements);
	  break;
	case C_STRTAG:
	case C_ENTAG:
	case C_UNTAG:
	  /* Various definition */
	  i = do_define (i, top_scope);
	  break;
	case C_EXT:
	case C_LABEL:
	  i = do_define (i, file_scope);
	  break;
	case C_STAT:
	case C_TPDEF:
	case C_AUTO:
	case C_REG:
	  i = do_define (i, top_scope);
	  break;
	default:
	  abort ();
	case C_EOS:
	  i += sym->n_numaux + 1;
	  break;
	}
    }
  do_sections_p2 (head);
  return head;
}