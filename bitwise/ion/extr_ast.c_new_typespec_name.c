#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t num_names; int /*<<< orphan*/  names; } ;
typedef  TYPE_1__ Typespec ;
typedef  int /*<<< orphan*/  SrcPos ;

/* Variables and functions */
 int /*<<< orphan*/  AST_DUP (char const**) ; 
 int /*<<< orphan*/  TYPESPEC_NAME ; 
 TYPE_1__* new_typespec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Typespec *new_typespec_name(SrcPos pos, const char **names, size_t num_names) {
    Typespec *t = new_typespec(TYPESPEC_NAME, pos);
    t->names = AST_DUP(names);
    t->num_names = num_names;
    return t;

}