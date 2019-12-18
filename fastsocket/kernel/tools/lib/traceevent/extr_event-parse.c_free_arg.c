#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {struct print_arg* args; } ;
struct TYPE_20__ {struct print_arg* right; struct print_arg* left; struct print_arg* op; } ;
struct TYPE_19__ {struct print_arg* index; } ;
struct TYPE_18__ {struct print_arg* string; } ;
struct TYPE_17__ {struct print_arg* item; struct print_arg* type; } ;
struct TYPE_16__ {struct print_arg* size; struct print_arg* field; } ;
struct TYPE_15__ {int /*<<< orphan*/  symbols; struct print_arg* field; } ;
struct TYPE_14__ {int /*<<< orphan*/  flags; struct print_arg* delim; struct print_arg* field; } ;
struct TYPE_13__ {struct print_arg* name; } ;
struct TYPE_12__ {struct print_arg* atom; } ;
struct print_arg {int type; struct print_arg* next; TYPE_10__ func; TYPE_9__ op; TYPE_8__ dynarray; TYPE_7__ string; TYPE_6__ typecast; TYPE_5__ hex; TYPE_4__ symbol; TYPE_3__ flags; TYPE_2__ field; TYPE_1__ atom; } ;

/* Variables and functions */
#define  PRINT_ATOM 139 
#define  PRINT_BSTRING 138 
#define  PRINT_DYNAMIC_ARRAY 137 
#define  PRINT_FIELD 136 
#define  PRINT_FLAGS 135 
#define  PRINT_FUNC 134 
#define  PRINT_HEX 133 
#define  PRINT_NULL 132 
#define  PRINT_OP 131 
#define  PRINT_STRING 130 
#define  PRINT_SYMBOL 129 
#define  PRINT_TYPE 128 
 int /*<<< orphan*/  free (struct print_arg*) ; 
 int /*<<< orphan*/  free_flag_sym (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_arg(struct print_arg *arg)
{
	struct print_arg *farg;

	if (!arg)
		return;

	switch (arg->type) {
	case PRINT_ATOM:
		free(arg->atom.atom);
		break;
	case PRINT_FIELD:
		free(arg->field.name);
		break;
	case PRINT_FLAGS:
		free_arg(arg->flags.field);
		free(arg->flags.delim);
		free_flag_sym(arg->flags.flags);
		break;
	case PRINT_SYMBOL:
		free_arg(arg->symbol.field);
		free_flag_sym(arg->symbol.symbols);
		break;
	case PRINT_HEX:
		free_arg(arg->hex.field);
		free_arg(arg->hex.size);
		break;
	case PRINT_TYPE:
		free(arg->typecast.type);
		free_arg(arg->typecast.item);
		break;
	case PRINT_STRING:
	case PRINT_BSTRING:
		free(arg->string.string);
		break;
	case PRINT_DYNAMIC_ARRAY:
		free(arg->dynarray.index);
		break;
	case PRINT_OP:
		free(arg->op.op);
		free_arg(arg->op.left);
		free_arg(arg->op.right);
		break;
	case PRINT_FUNC:
		while (arg->func.args) {
			farg = arg->func.args;
			arg->func.args = farg->next;
			free_arg(farg);
		}
		break;

	case PRINT_NULL:
	default:
		break;
	}

	free(arg);
}