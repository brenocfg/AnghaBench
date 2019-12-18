#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_5__ {int kind; int /*<<< orphan*/  fields; int /*<<< orphan*/  is_struct; struct TYPE_5__* ptr; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
#define  KIND_ARRAY 130 
#define  KIND_PTR 129 
#define  KIND_STRUCT 128 
 int /*<<< orphan*/ * dict_keys (int /*<<< orphan*/ ) ; 
 TYPE_1__* vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool is_same_struct(Type *a, Type *b) {
    if (a->kind != b->kind)
        return false;
    switch (a->kind) {
    case KIND_ARRAY:
        return a->len == b->len &&
            is_same_struct(a->ptr, b->ptr);
    case KIND_PTR:
        return is_same_struct(a->ptr, b->ptr);
    case KIND_STRUCT: {
        if (a->is_struct != b->is_struct)
            return false;
        Vector *ka = dict_keys(a->fields);
        Vector *kb = dict_keys(b->fields);
        if (vec_len(ka) != vec_len(kb))
            return false;
        for (int i = 0; i < vec_len(ka); i++)
            if (!is_same_struct(vec_get(ka, i), vec_get(kb, i)))
                return false;
        return true;
    }
    default:
        return true;
    }
}