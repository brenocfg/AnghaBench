#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  elements; } ;
struct TYPE_22__ {TYPE_8__* ref; } ;
struct TYPE_20__ {TYPE_6__* ref; } ;
struct TYPE_18__ {int /*<<< orphan*/  elements; } ;
struct TYPE_17__ {int /*<<< orphan*/  code; int /*<<< orphan*/  parameters; int /*<<< orphan*/  lines; struct coff_type* function_returns; } ;
struct TYPE_16__ {int dim; struct coff_type* array_of; } ;
struct TYPE_15__ {struct coff_type* points_to; } ;
struct TYPE_14__ {int address; int size; } ;
struct TYPE_13__ {int /*<<< orphan*/  basic; TYPE_10__ aenumdef; TYPE_9__ astructref; TYPE_7__ aenumref; TYPE_5__ astructdef; TYPE_4__ function; TYPE_3__ array; TYPE_2__ pointer; TYPE_1__ asecdef; } ;
struct coff_type {int size; int type; TYPE_11__ u; } ;
struct TYPE_21__ {char* name; } ;
struct TYPE_19__ {char* name; } ;

/* Variables and functions */
#define  T_CHAR 153 
#define  T_DOUBLE 152 
#define  T_ENUM 151 
#define  T_FLOAT 150 
#define  T_INT 149 
#define  T_LNGDBL 148 
#define  T_LONG 147 
#define  T_MOE 146 
#define  T_NULL 145 
#define  T_SHORT 144 
#define  T_STRUCT 143 
#define  T_UCHAR 142 
#define  T_UINT 141 
#define  T_ULONG 140 
#define  T_UNION 139 
#define  T_USHORT 138 
#define  T_VOID 137 
 int /*<<< orphan*/  abort () ; 
#define  coff_array_type 136 
#define  coff_basic_type 135 
#define  coff_enumdef_type 134 
#define  coff_enumref_type 133 
#define  coff_function_type 132 
#define  coff_pointer_type 131 
#define  coff_secdef_type 130 
#define  coff_structdef_type 129 
#define  coff_structref_type 128 
 int /*<<< orphan*/  dump_coff_lines (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_coff_scope (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  tab (int) ; 

__attribute__((used)) static void
dump_coff_type (struct coff_type *p)
{
  tab (1);
  printf ("size %d ", p->size);

  switch (p->type)
    {
    case coff_secdef_type:
      printf ("section definition at %x size %x\n",
	      p->u.asecdef.address,
	      p->u.asecdef.size);
      nl ();
      break;
    case coff_pointer_type:
      printf ("pointer to");
      nl ();
      dump_coff_type (p->u.pointer.points_to);
      break;
    case coff_array_type:
      printf ("array [%d] of", p->u.array.dim);
      nl ();
      dump_coff_type (p->u.array.array_of);
      break;
    case coff_function_type:
      printf ("function returning");
      nl ();
      dump_coff_type (p->u.function.function_returns);
      dump_coff_lines (p->u.function.lines);
      printf ("arguments");
      nl ();
      dump_coff_scope (p->u.function.parameters);
      tab (0);
      printf ("code");
      nl ();
      dump_coff_scope (p->u.function.code);
      tab(0);
      break;
    case coff_structdef_type:
      printf ("structure definition");
      nl ();
      dump_coff_scope (p->u.astructdef.elements);
      break;
    case coff_structref_type:
      if (!p->u.aenumref.ref)
	printf ("structure ref to UNKNOWN struct");
      else
	printf ("structure ref to %s", p->u.aenumref.ref->name);
      break;
    case coff_enumref_type:
      printf ("enum ref to %s", p->u.astructref.ref->name);
      break;
    case coff_enumdef_type:
      printf ("enum definition");
      nl ();
      dump_coff_scope (p->u.aenumdef.elements);
      break;
    case coff_basic_type:
      switch (p->u.basic)
	{
	case T_NULL:
	  printf ("NULL");
	  break;
	case T_VOID:
	  printf ("VOID");
	  break;
	case T_CHAR:
	  printf ("CHAR");
	  break;
	case T_SHORT:
	  printf ("SHORT");
	  break;
	case T_INT:
	  printf ("INT ");
	  break;
	case T_LONG:
	  printf ("LONG");
	  break;
	case T_FLOAT:
	  printf ("FLOAT");
	  break;
	case T_DOUBLE:
	  printf ("DOUBLE");
	  break;
	case T_STRUCT:
	  printf ("STRUCT");
	  break;
	case T_UNION:
	  printf ("UNION");
	  break;
	case T_ENUM:
	  printf ("ENUM");
	  break;
	case T_MOE:
	  printf ("MOE ");
	  break;
	case T_UCHAR:
	  printf ("UCHAR");
	  break;
	case T_USHORT:
	  printf ("USHORT");
	  break;
	case T_UINT:
	  printf ("UINT");
	  break;
	case T_ULONG:
	  printf ("ULONG");
	  break;
	case T_LNGDBL:
	  printf ("LNGDBL");
	  break;
	default:
	  abort ();
	}
    }
  nl ();
  tab (-1);
}