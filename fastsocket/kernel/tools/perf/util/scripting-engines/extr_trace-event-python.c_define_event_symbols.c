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
struct TYPE_14__ {struct print_arg* size; struct print_arg* field; } ;
struct TYPE_13__ {struct print_arg* right; struct print_arg* left; int /*<<< orphan*/  op; } ;
struct TYPE_12__ {struct print_arg* item; } ;
struct TYPE_11__ {int /*<<< orphan*/  symbols; struct print_arg* field; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * delim; struct print_arg* field; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  atom; } ;
struct print_arg {int type; struct print_arg* next; TYPE_7__ hex; TYPE_6__ op; TYPE_5__ typecast; TYPE_4__ symbol; TYPE_3__ flags; TYPE_2__ field; TYPE_1__ atom; } ;
struct event_format {int dummy; } ;

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
 int /*<<< orphan*/  cur_field_name ; 
 int /*<<< orphan*/  define_field (int const,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  define_value (int,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  define_values (int const,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int zero_flag_atom ; 

__attribute__((used)) static void define_event_symbols(struct event_format *event,
				 const char *ev_name,
				 struct print_arg *args)
{
	switch (args->type) {
	case PRINT_NULL:
		break;
	case PRINT_ATOM:
		define_value(PRINT_FLAGS, ev_name, cur_field_name, "0",
			     args->atom.atom);
		zero_flag_atom = 0;
		break;
	case PRINT_FIELD:
		if (cur_field_name)
			free(cur_field_name);
		cur_field_name = strdup(args->field.name);
		break;
	case PRINT_FLAGS:
		define_event_symbols(event, ev_name, args->flags.field);
		define_field(PRINT_FLAGS, ev_name, cur_field_name,
			     args->flags.delim);
		define_values(PRINT_FLAGS, args->flags.flags, ev_name,
			      cur_field_name);
		break;
	case PRINT_SYMBOL:
		define_event_symbols(event, ev_name, args->symbol.field);
		define_field(PRINT_SYMBOL, ev_name, cur_field_name, NULL);
		define_values(PRINT_SYMBOL, args->symbol.symbols, ev_name,
			      cur_field_name);
		break;
	case PRINT_STRING:
		break;
	case PRINT_TYPE:
		define_event_symbols(event, ev_name, args->typecast.item);
		break;
	case PRINT_OP:
		if (strcmp(args->op.op, ":") == 0)
			zero_flag_atom = 1;
		define_event_symbols(event, ev_name, args->op.left);
		define_event_symbols(event, ev_name, args->op.right);
		break;
	case PRINT_HEX:
		define_event_symbols(event, ev_name, args->hex.field);
		define_event_symbols(event, ev_name, args->hex.size);
		break;
	default:
		/* gcc warns for these? */
	case PRINT_BSTRING:
	case PRINT_DYNAMIC_ARRAY:
	case PRINT_FUNC:
		/* we should warn... */
		return;
	}

	if (args->next)
		define_event_symbols(event, ev_name, args->next);
}