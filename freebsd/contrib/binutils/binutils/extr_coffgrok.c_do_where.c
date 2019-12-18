#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct internal_syment {int n_value; int n_scnum; int n_sclass; } ;
struct coff_where {int offset; int bitoffset; void* where; int /*<<< orphan*/ * section; int /*<<< orphan*/  bitsize; } ;
struct TYPE_14__ {int /*<<< orphan*/ * sections; } ;
struct TYPE_8__ {int /*<<< orphan*/  x_size; } ;
struct TYPE_9__ {TYPE_1__ x_lnsz; } ;
struct TYPE_10__ {TYPE_2__ x_misc; } ;
struct TYPE_11__ {TYPE_3__ x_sym; } ;
struct TYPE_12__ {TYPE_4__ auxent; struct internal_syment syment; } ;
struct TYPE_13__ {TYPE_5__ u; } ;

/* Variables and functions */
#define  C_ARG 143 
#define  C_AUTO 142 
#define  C_ENTAG 141 
#define  C_EXT 140 
#define  C_EXTDEF 139 
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
 int /*<<< orphan*/  abort () ; 
 void* coff_where_entag ; 
 void* coff_where_member_of_enum ; 
 void* coff_where_member_of_struct ; 
 void* coff_where_memory ; 
 void* coff_where_register ; 
 void* coff_where_stack ; 
 void* coff_where_strtag ; 
 void* coff_where_typedef ; 
 TYPE_7__* ofile ; 
 TYPE_6__* rawsyms ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static struct coff_where *
do_where (int i)
{
  struct internal_syment *sym = &rawsyms[i].u.syment;
  struct coff_where *where =
    (struct coff_where *) (xmalloc (sizeof (struct coff_where)));
  where->offset = sym->n_value;

  if (sym->n_scnum == -1)
    sym->n_scnum = 0;

  switch (sym->n_sclass)
    {
    case C_FIELD:
      where->where = coff_where_member_of_struct;
      where->offset = sym->n_value / 8;
      where->bitoffset = sym->n_value % 8;
      where->bitsize = rawsyms[i + 1].u.auxent.x_sym.x_misc.x_lnsz.x_size;
      break;
    case C_MOE:
      where->where = coff_where_member_of_enum;
      break;
    case C_MOS:
    case C_MOU:
      where->where = coff_where_member_of_struct;
      break;
    case C_AUTO:
    case C_ARG:
      where->where = coff_where_stack;
      break;
    case C_EXT:
    case C_STAT:
    case C_EXTDEF:
    case C_LABEL:
      where->where = coff_where_memory;
      where->section = &ofile->sections[sym->n_scnum];
      break;
    case C_REG:
    case C_REGPARM:
      where->where = coff_where_register;
      break;
    case C_ENTAG:
      where->where = coff_where_entag;
      break;
    case C_STRTAG:
    case C_UNTAG:
      where->where = coff_where_strtag;
      break;
    case C_TPDEF:
      where->where = coff_where_typedef;
      break;
    default:
      abort ();
      break;
    }
  return where;
}