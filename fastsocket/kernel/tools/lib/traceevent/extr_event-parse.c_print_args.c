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
struct trace_seq {int dummy; } ;
struct TYPE_16__ {char* op; struct print_arg* right; struct print_arg* left; } ;
struct TYPE_15__ {char* type; struct print_arg* item; } ;
struct TYPE_14__ {char* string; } ;
struct TYPE_13__ {struct print_arg* size; struct print_arg* field; } ;
struct TYPE_12__ {int /*<<< orphan*/  symbols; struct print_arg* field; } ;
struct TYPE_11__ {char* delim; int /*<<< orphan*/  flags; struct print_arg* field; } ;
struct TYPE_10__ {char* name; } ;
struct TYPE_9__ {char* atom; } ;
struct print_arg {int type; struct print_arg* next; TYPE_8__ op; TYPE_7__ typecast; TYPE_6__ string; TYPE_5__ hex; TYPE_4__ symbol; TYPE_3__ flags; TYPE_2__ field; TYPE_1__ atom; } ;

/* Variables and functions */
#define  PRINT_ATOM 137 
#define  PRINT_BSTRING 136 
#define  PRINT_FIELD 135 
#define  PRINT_FLAGS 134 
#define  PRINT_HEX 133 
#define  PRINT_NULL 132 
#define  PRINT_OP 131 
#define  PRINT_STRING 130 
#define  PRINT_SYMBOL 129 
#define  PRINT_TYPE 128 
 int /*<<< orphan*/  print_fields (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  trace_seq_destroy (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_do_printf (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_init (struct trace_seq*) ; 

__attribute__((used)) static void print_args(struct print_arg *args)
{
	int print_paren = 1;
	struct trace_seq s;

	switch (args->type) {
	case PRINT_NULL:
		printf("null");
		break;
	case PRINT_ATOM:
		printf("%s", args->atom.atom);
		break;
	case PRINT_FIELD:
		printf("REC->%s", args->field.name);
		break;
	case PRINT_FLAGS:
		printf("__print_flags(");
		print_args(args->flags.field);
		printf(", %s, ", args->flags.delim);
		trace_seq_init(&s);
		print_fields(&s, args->flags.flags);
		trace_seq_do_printf(&s);
		trace_seq_destroy(&s);
		printf(")");
		break;
	case PRINT_SYMBOL:
		printf("__print_symbolic(");
		print_args(args->symbol.field);
		printf(", ");
		trace_seq_init(&s);
		print_fields(&s, args->symbol.symbols);
		trace_seq_do_printf(&s);
		trace_seq_destroy(&s);
		printf(")");
		break;
	case PRINT_HEX:
		printf("__print_hex(");
		print_args(args->hex.field);
		printf(", ");
		print_args(args->hex.size);
		printf(")");
		break;
	case PRINT_STRING:
	case PRINT_BSTRING:
		printf("__get_str(%s)", args->string.string);
		break;
	case PRINT_TYPE:
		printf("(%s)", args->typecast.type);
		print_args(args->typecast.item);
		break;
	case PRINT_OP:
		if (strcmp(args->op.op, ":") == 0)
			print_paren = 0;
		if (print_paren)
			printf("(");
		print_args(args->op.left);
		printf(" %s ", args->op.op);
		print_args(args->op.right);
		if (print_paren)
			printf(")");
		break;
	default:
		/* we should warn... */
		return;
	}
	if (args->next) {
		printf("\n");
		print_args(args->next);
	}
}