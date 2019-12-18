#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * _n_nptr; } ;
struct internal_syment {int n_numaux; TYPE_2__ _n; } ;
struct coff_symbol {int number; TYPE_7__* type; TYPE_6__* where; int /*<<< orphan*/  visible; struct coff_symbol* next; struct coff_symbol* next_in_ofile_list; TYPE_8__* sfile; int /*<<< orphan*/  name; } ;
struct coff_scope {int /*<<< orphan*/  nvars; struct coff_symbol* vars_tail; struct coff_symbol* vars_head; } ;
struct coff_isection {int init; TYPE_3__* parent; scalar_t__ high; scalar_t__ low; } ;
struct TYPE_16__ {struct coff_isection* section; } ;
struct TYPE_15__ {scalar_t__ type; scalar_t__ size; } ;
struct TYPE_14__ {scalar_t__ where; TYPE_3__* section; scalar_t__ offset; } ;
struct TYPE_13__ {struct coff_symbol* symbol_list_tail; struct coff_symbol* symbol_list_head; } ;
struct TYPE_9__ {struct internal_syment syment; } ;
struct TYPE_12__ {TYPE_1__ u; } ;
struct TYPE_11__ {int number; } ;

/* Variables and functions */
 scalar_t__ coff_function_type ; 
 scalar_t__ coff_secdef_type ; 
 scalar_t__ coff_where_memory ; 
 TYPE_8__* cur_sfile ; 
 TYPE_7__* do_type (int) ; 
 int /*<<< orphan*/  do_visible (int) ; 
 TYPE_6__* do_where (int) ; 
 struct coff_symbol* empty_symbol () ; 
 struct coff_symbol* last_function_symbol ; 
 scalar_t__ lofile ; 
 TYPE_5__* ofile ; 
 TYPE_4__* rawsyms ; 
 struct coff_symbol** tindex ; 

__attribute__((used)) static int
do_define (int i, struct coff_scope *b)
{
  static int symbol_index;
  struct internal_syment *sym = &rawsyms[i].u.syment;

  /* Define a symbol and attach to block b */
  struct coff_symbol *s = empty_symbol ();

  s->number = ++symbol_index;
  s->name = sym->_n._n_nptr[1];
  s->sfile = cur_sfile;
  /* Glue onto the ofile list */
  if (lofile >= 0)
    {
      if (ofile->symbol_list_tail)
	ofile->symbol_list_tail->next_in_ofile_list = s;
      else
	ofile->symbol_list_head = s;
      ofile->symbol_list_tail = s;
      /* And the block list */
    }
  if (b->vars_tail)
    b->vars_tail->next = s;
  else
    b->vars_head = s;

  b->vars_tail = s;
  b->nvars++;
  s->type = do_type (i);
  s->where = do_where (i);
  s->visible = do_visible (i);

  tindex[i] = s;

  /* We remember the lowest address in each section for each source file */

  if (s->where->where == coff_where_memory
      && s->type->type == coff_secdef_type)
    {
      struct coff_isection *is = cur_sfile->section + s->where->section->number;

      if (!is->init)
	{
	  is->low = s->where->offset;
	  is->high = s->where->offset + s->type->size;
	  is->init = 1;
	  is->parent = s->where->section;
	}

    }

  if (s->type->type == coff_function_type)
    last_function_symbol = s;

  return i + sym->n_numaux + 1;
}