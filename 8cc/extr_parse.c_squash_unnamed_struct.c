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
struct TYPE_5__ {int offset; int /*<<< orphan*/  fields; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Dict ;

/* Variables and functions */
 TYPE_1__* copy_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dict_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dict_keys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dict_put (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 char* vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void squash_unnamed_struct(Dict *dict, Type *unnamed, int offset) {
    Vector *keys = dict_keys(unnamed->fields);
    for (int i = 0; i < vec_len(keys); i++) {
        char *name = vec_get(keys, i);
        Type *t = copy_type(dict_get(unnamed->fields, name));
        t->offset += offset;
        dict_put(dict, name, t);
    }
}