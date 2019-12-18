#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ kind; int is_struct; int align; int size; int /*<<< orphan*/ * fields; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Dict ;

/* Variables and functions */
 scalar_t__ KIND_ENUM ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 TYPE_1__* make_rectype (int) ; 
 TYPE_1__* map_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/ * read_rectype_fields (int*,int*,int) ; 
 char* read_rectype_tag () ; 
 int /*<<< orphan*/  tags ; 

__attribute__((used)) static Type *read_rectype_def(bool is_struct) {
    char *tag = read_rectype_tag();
    Type *r;
    if (tag) {
        r = map_get(tags, tag);
        if (r && (r->kind == KIND_ENUM || r->is_struct != is_struct))
            error("declarations of %s does not match", tag);
        if (!r) {
            r = make_rectype(is_struct);
            map_put(tags, tag, r);
        }
    } else {
        r = make_rectype(is_struct);
    }
    int size = 0, align = 1;
    Dict *fields = read_rectype_fields(&size, &align, is_struct);
    r->align = align;
    if (fields) {
        r->fields = fields;
        r->size = size;
    }
    return r;
}