#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t num_fields; int /*<<< orphan*/  fields; } ;
struct TYPE_8__ {TYPE_1__ tuple; } ;
typedef  TYPE_2__ Typespec ;
typedef  int /*<<< orphan*/  SrcPos ;

/* Variables and functions */
 int /*<<< orphan*/  AST_DUP (TYPE_2__**) ; 
 int /*<<< orphan*/  TYPESPEC_TUPLE ; 
 TYPE_2__* new_typespec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Typespec *new_typespec_tuple(SrcPos pos, Typespec **fields, size_t num_fields) {
    Typespec *t = new_typespec(TYPESPEC_TUPLE, pos);
    t->tuple.fields = AST_DUP(fields);
    t->tuple.num_fields = num_fields;
    return t;
}