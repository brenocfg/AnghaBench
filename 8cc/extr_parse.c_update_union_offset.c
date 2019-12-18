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
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_4__ {scalar_t__ kind; scalar_t__ bitsize; scalar_t__ bitoff; scalar_t__ offset; int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Dict ;

/* Variables and functions */
 scalar_t__ KIND_STRUCT ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 int compute_padding (int,int) ; 
 int /*<<< orphan*/  dict_put (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/ * make_dict () ; 
 int /*<<< orphan*/  squash_unnamed_struct (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 void** vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Dict *update_union_offset(int *rsize, int *align, Vector *fields) {
    int maxsize = 0;
    Dict *r = make_dict();
    for (int i = 0; i < vec_len(fields); i++) {
        void **pair = vec_get(fields, i);
        char *name = pair[0];
        Type *fieldtype = pair[1];
        maxsize = MAX(maxsize, fieldtype->size);
        *align = MAX(*align, fieldtype->align);
        if (name == NULL && fieldtype->kind == KIND_STRUCT) {
            squash_unnamed_struct(r, fieldtype, 0);
            continue;
        }
        fieldtype->offset = 0;
        if (fieldtype->bitsize >= 0)
            fieldtype->bitoff = 0;
        if (name)
            dict_put(r, name, fieldtype);
    }
    *rsize = maxsize + compute_padding(maxsize, *align);
    return r;
}