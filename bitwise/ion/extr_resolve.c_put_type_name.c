#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t num_fields; TYPE_2__* fields; } ;
struct TYPE_8__ {size_t num_params; TYPE_4__* ret; int /*<<< orphan*/  has_varargs; TYPE_4__** params; } ;
struct TYPE_11__ {size_t kind; TYPE_3__ aggregate; TYPE_1__ func; int /*<<< orphan*/  num_elems; struct TYPE_11__* base; TYPE_7__* sym; } ;
typedef  TYPE_4__ Type ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_4__* type; } ;

/* Variables and functions */
#define  TYPE_ARRAY 136 
#define  TYPE_CONST 135 
#define  TYPE_ENUM 134 
#define  TYPE_FUNC 133 
#define  TYPE_INCOMPLETE 132 
#define  TYPE_PTR 131 
#define  TYPE_STRUCT 130 
#define  TYPE_TUPLE 129 
#define  TYPE_UNION 128 
 int /*<<< orphan*/  assert (TYPE_7__*) ; 
 int /*<<< orphan*/  buf_printf (char*,char*,...) ; 
 char** type_names ; 
 TYPE_4__* type_void ; 

void put_type_name(char **buf, Type *type) {
    const char *type_name = type_names[type->kind];
    if (type_name) {
        buf_printf(*buf, "%s", type_name);
    } else {
        switch (type->kind) {
        case TYPE_STRUCT:
        case TYPE_UNION:
        case TYPE_ENUM:
        case TYPE_INCOMPLETE:
            assert(type->sym);
            buf_printf(*buf, "%s", type->sym->name);
            break;
        case TYPE_CONST:
            put_type_name(buf, type->base);
            buf_printf(*buf, " const");
            break;
        case TYPE_PTR:
            put_type_name(buf, type->base);
            buf_printf(*buf, "*");
            break;
        case TYPE_ARRAY:
            put_type_name(buf, type->base);
            buf_printf(*buf, "[%zu]", type->num_elems);
            break;
        case TYPE_FUNC:
            buf_printf(*buf, "func(");
            for (size_t i = 0; i < type->func.num_params; i++) {
                if (i != 0) {
                    buf_printf(*buf, ", ");
                }
                put_type_name(buf, type->func.params[i]);
            }
            if (type->func.has_varargs) {
                buf_printf(*buf, "...");
            }
            buf_printf(*buf, ")");
            if (type->func.ret != type_void) {
                buf_printf(*buf, ": ");
                put_type_name(buf, type->func.ret);
            }
            break;
        case TYPE_TUPLE:
            buf_printf(*buf, "{");
            for (size_t i = 0; i < type->aggregate.num_fields; i++) {
                if (i != 0) {
                    buf_printf(*buf, ", ");
                }
                put_type_name(buf, type->aggregate.fields[i].type);
            }
            buf_printf(*buf, "}");
            break;
        default:
            assert(0);
            break;
        }
    }
}