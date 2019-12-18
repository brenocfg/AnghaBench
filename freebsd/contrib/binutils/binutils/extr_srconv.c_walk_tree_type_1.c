#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_8__* ref; } ;
struct TYPE_24__ {TYPE_6__* elements; int /*<<< orphan*/  idx; } ;
struct TYPE_22__ {int dim; struct coff_type* array_of; } ;
struct TYPE_21__ {TYPE_3__* ref; } ;
struct TYPE_19__ {TYPE_1__* elements; int /*<<< orphan*/  idx; } ;
struct TYPE_16__ {TYPE_11__* parameters; struct coff_type* function_returns; } ;
struct TYPE_14__ {struct coff_type* points_to; } ;
struct TYPE_17__ {TYPE_9__ aenumref; TYPE_7__ aenumdef; TYPE_5__ array; TYPE_4__ astructref; TYPE_2__ astructdef; TYPE_12__ function; TYPE_10__ pointer; int /*<<< orphan*/  basic; } ;
struct coff_type {int type; int size; TYPE_13__ u; } ;
struct coff_symbol {struct coff_symbol* next; } ;
struct coff_sfile {int dummy; } ;
struct IT_dpt {int neg; int /*<<< orphan*/  dunno; } ;
struct IT_dfp {int end; int neg; int /*<<< orphan*/  nparams; int /*<<< orphan*/  spare; } ;
struct IT_den {int end; int neg; int /*<<< orphan*/  spare; } ;
struct IT_dds {int end; int neg; int /*<<< orphan*/  spare; } ;
struct IT_dbt {int bitsize; int neg; void* sid; void* fptype; void* sign; void* btype; } ;
struct IT_dar {int dims; int* max; int* min; int neg; int length; int /*<<< orphan*/ * min_variable; int /*<<< orphan*/ * max_variable; int /*<<< orphan*/ * spare; int /*<<< orphan*/ * subtype; int /*<<< orphan*/ * variable; void* minspare; void* maxspare; } ;
struct TYPE_25__ {int /*<<< orphan*/  number; } ;
struct TYPE_23__ {struct coff_symbol* vars_head; } ;
struct TYPE_20__ {int /*<<< orphan*/  number; } ;
struct TYPE_18__ {struct coff_symbol* vars_head; } ;
struct TYPE_15__ {struct coff_symbol* vars_head; int /*<<< orphan*/  nvars; } ;

/* Variables and functions */
 void* BTYPE_CHAR ; 
 void* BTYPE_ENUM ; 
 void* BTYPE_FLOAT ; 
 void* BTYPE_INT ; 
 void* BTYPE_STRUCT ; 
 void* BTYPE_TAG ; 
 void* BTYPE_UNSPEC ; 
 void* BTYPE_VOID ; 
 void* FPTYPE_DOUBLE ; 
 void* FPTYPE_EXTENDED ; 
 void* FPTYPE_NOTSPEC ; 
 void* FPTYPE_SINGLE ; 
 void* SIGN_SIGNED ; 
 void* SIGN_UNSIGNED ; 
 void* SIGN_UNSPEC ; 
 int /*<<< orphan*/  SUB_INTEGER ; 
#define  T_CHAR 149 
#define  T_DOUBLE 148 
#define  T_FLOAT 147 
#define  T_INT 146 
#define  T_LNGDBL 145 
#define  T_LONG 144 
#define  T_NULL 143 
#define  T_SHORT 142 
#define  T_UCHAR 141 
#define  T_UINT 140 
#define  T_ULONG 139 
#define  T_USHORT 138 
#define  T_VOID 137 
 int /*<<< orphan*/  VARIABLE_FIXED ; 
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
 int /*<<< orphan*/  file ; 
 void* get_member_id (int /*<<< orphan*/ ) ; 
 void* nints (int) ; 
 int /*<<< orphan*/  sysroff_swap_dar_out (int /*<<< orphan*/ ,struct IT_dar*) ; 
 int /*<<< orphan*/  sysroff_swap_dbt_out (int /*<<< orphan*/ ,struct IT_dbt*) ; 
 int /*<<< orphan*/  sysroff_swap_dds_out (int /*<<< orphan*/ ,struct IT_dds*) ; 
 int /*<<< orphan*/  sysroff_swap_den_out (int /*<<< orphan*/ ,struct IT_den*) ; 
 int /*<<< orphan*/  sysroff_swap_dfp_out (int /*<<< orphan*/ ,struct IT_dfp*) ; 
 int /*<<< orphan*/  sysroff_swap_dpt_out (int /*<<< orphan*/ ,struct IT_dpt*) ; 
 int /*<<< orphan*/  walk_tree_symbol (struct coff_sfile*,int /*<<< orphan*/ ,struct coff_symbol*,int) ; 

__attribute__((used)) static void
walk_tree_type_1 (struct coff_sfile *sfile, struct coff_symbol *symbol,
		  struct coff_type *type, int nest)
{
  switch (type->type)
    {
    case coff_secdef_type:
    case coff_basic_type:
      {
	struct IT_dbt dbt;

	switch (type->u.basic)
	  {
	  case T_NULL:
	  case T_VOID:
	    dbt.btype = BTYPE_VOID;
	    dbt.sign = BTYPE_UNSPEC;
	    dbt.fptype = FPTYPE_NOTSPEC;
	    break;

	  case T_CHAR:
	    dbt.btype = BTYPE_CHAR;
	    dbt.sign = BTYPE_UNSPEC;
	    dbt.fptype = FPTYPE_NOTSPEC;
	    break;

	  case T_SHORT:
	  case T_INT:
	  case T_LONG:
	    dbt.btype = BTYPE_INT;
	    dbt.sign = SIGN_SIGNED;
	    dbt.fptype = FPTYPE_NOTSPEC;
	    break;

	  case T_FLOAT:
	    dbt.btype = BTYPE_FLOAT;
	    dbt.fptype = FPTYPE_SINGLE;
	    break;

	  case T_DOUBLE:
	    dbt.btype = BTYPE_FLOAT;
	    dbt.fptype = FPTYPE_DOUBLE;
	    break;

	  case T_LNGDBL:
	    dbt.btype = BTYPE_FLOAT;
	    dbt.fptype = FPTYPE_EXTENDED;
	    break;

	  case T_UCHAR:
	    dbt.btype = BTYPE_CHAR;
	    dbt.sign = SIGN_UNSIGNED;
	    dbt.fptype = FPTYPE_NOTSPEC;
	    break;

	  case T_USHORT:
	  case T_UINT:
	  case T_ULONG:
	    dbt.btype = BTYPE_INT;
	    dbt.sign = SIGN_UNSIGNED;
	    dbt.fptype = FPTYPE_NOTSPEC;
	    break;
	  }

	dbt.bitsize = type->size;
	dbt.neg = 0x1001;
	sysroff_swap_dbt_out (file, &dbt);
	break;
      }

    case coff_pointer_type:
      {
	struct IT_dpt dpt;

	dpt.dunno = 0;
	walk_tree_type_1 (sfile, symbol, type->u.pointer.points_to, nest + 1);
	dpt.neg = 0x1001;
	sysroff_swap_dpt_out (file, &dpt);
	break;
      }

    case coff_function_type:
      {
	struct IT_dfp dfp;
	struct coff_symbol *param;

	dfp.end = 0;
	dfp.spare = 0;
	dfp.nparams = type->u.function.parameters->nvars;
	dfp.neg = 0x1001;

	walk_tree_type_1 (sfile, symbol, type->u.function.function_returns, nest + 1);

	sysroff_swap_dfp_out (file, &dfp);

	for (param = type->u.function.parameters->vars_head;
	     param;
	     param = param->next)
	  walk_tree_symbol (sfile, 0, param, nest);

	dfp.end = 1;
	sysroff_swap_dfp_out (file, &dfp);
	break;
      }

    case coff_structdef_type:
      {
	struct IT_dbt dbt;
	struct IT_dds dds;
	struct coff_symbol *member;

	dds.spare = 0;
	dbt.btype = BTYPE_STRUCT;
	dbt.bitsize = type->size;
	dbt.sign = SIGN_UNSPEC;
	dbt.fptype = FPTYPE_NOTSPEC;
	dbt.sid = get_member_id (type->u.astructdef.idx);
	dbt.neg = 0x1001;
	sysroff_swap_dbt_out (file, &dbt);
	dds.end = 0;
	dds.neg = 0x1001;
	sysroff_swap_dds_out (file, &dds);

	for (member = type->u.astructdef.elements->vars_head;
	     member;
	     member = member->next)
	  walk_tree_symbol (sfile, 0, member, nest + 1);

	dds.end = 1;
	sysroff_swap_dds_out (file, &dds);

      }
      break;

    case coff_structref_type:
      {
	struct IT_dbt dbt;

	dbt.btype = BTYPE_TAG;
	dbt.bitsize = type->size;
	dbt.sign = SIGN_UNSPEC;
	dbt.fptype = FPTYPE_NOTSPEC;

	if (type->u.astructref.ref)
	  dbt.sid = get_member_id (type->u.astructref.ref->number);
	else
	  dbt.sid = 0;

	dbt.neg = 0x1001;
	sysroff_swap_dbt_out (file, &dbt);
      }
      break;

    case coff_array_type:
      {
	struct IT_dar dar;
	int j;
	int dims = 1;		/* Only output one dimension at a time.  */

	dar.dims = dims;
	dar.variable = nints (dims);
	dar.subtype = nints (dims);
	dar.spare = nints (dims);
	dar.max_variable = nints (dims);
	dar.maxspare = nints (dims);
	dar.max = nints (dims);
	dar.min_variable = nints (dims);
	dar.min = nints (dims);
	dar.minspare = nints (dims);
	dar.neg = 0x1001;
	dar.length = type->size / type->u.array.dim;

	for (j = 0; j < dims; j++)
	  {
	    dar.variable[j] = VARIABLE_FIXED;
	    dar.subtype[j] = SUB_INTEGER;
	    dar.spare[j] = 0;
	    dar.max_variable[j] = 0;
	    dar.max[j] = type->u.array.dim;
	    dar.min_variable[j] = 0;
	    dar.min[j] = 1;	/* Why isn't this 0 ? */
	  }
	walk_tree_type_1 (sfile, symbol, type->u.array.array_of, nest + 1);
	sysroff_swap_dar_out (file, &dar);
      }
      break;

    case coff_enumdef_type:
      {
	struct IT_dbt dbt;
	struct IT_den den;
	struct coff_symbol *member;

	dbt.btype = BTYPE_ENUM;
	dbt.bitsize = type->size;
	dbt.sign = SIGN_UNSPEC;
	dbt.fptype = FPTYPE_NOTSPEC;
	dbt.sid = get_member_id (type->u.aenumdef.idx);
	dbt.neg = 0x1001;
	sysroff_swap_dbt_out (file, &dbt);

	den.end = 0;
	den.neg = 0x1001;
	den.spare = 0;
	sysroff_swap_den_out (file, &den);

	for (member = type->u.aenumdef.elements->vars_head;
	     member;
	     member = member->next)
	  walk_tree_symbol (sfile, 0, member, nest + 1);

	den.end = 1;
	sysroff_swap_den_out (file, &den);
      }
      break;

    case coff_enumref_type:
      {
	struct IT_dbt dbt;

	dbt.btype = BTYPE_TAG;
	dbt.bitsize = type->size;
	dbt.sign = SIGN_UNSPEC;
	dbt.fptype = FPTYPE_NOTSPEC;
	dbt.sid = get_member_id (type->u.aenumref.ref->number);
	dbt.neg = 0x1001;
	sysroff_swap_dbt_out (file, &dbt);
      }
      break;

    default:
      abort ();
    }
}