#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_3__ {int len; int size; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 int /*<<< orphan*/  ast_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ast_inttype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  type_char ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assign_string(Vector *inits, Type *ty, char *p, int off) {
    if (ty->len == -1)
        ty->len = ty->size = strlen(p) + 1;
    int i = 0;
    for (; i < ty->len && *p; i++)
        vec_push(inits, ast_init(ast_inttype(type_char, *p++), type_char, off + i));
    for (; i < ty->len; i++)
        vec_push(inits, ast_init(ast_inttype(type_char, 0), type_char, off + i));
}