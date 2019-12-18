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
struct TYPE_4__ {int align; scalar_t__ kind; int size; scalar_t__ bitsize; int offset; int bitoff; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Dict ;

/* Variables and functions */
 scalar_t__ KIND_STRUCT ; 
 int MAX (int,int) ; 
 int compute_padding (int,int) ; 
 int /*<<< orphan*/  dict_put (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  finish_bitfield (int*,int*) ; 
 int /*<<< orphan*/ * make_dict () ; 
 int /*<<< orphan*/  squash_unnamed_struct (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 void** vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Dict *update_struct_offset(int *rsize, int *align, Vector *fields) {
    int off = 0, bitoff = 0;
    Dict *r = make_dict();
    for (int i = 0; i < vec_len(fields); i++) {
        void **pair = vec_get(fields, i);
        char *name = pair[0];
        Type *fieldtype = pair[1];
        // C11 6.7.2.1p14: Each member is aligned to its natural boundary.
        // As a result the entire struct is aligned to the largest among its members.
        // Unnamed fields will never be accessed, so they shouldn't be taken into account
        // when calculating alignment.
        if (name)
            *align = MAX(*align, fieldtype->align);

        if (name == NULL && fieldtype->kind == KIND_STRUCT) {
            // C11 6.7.2.1p13: Anonymous struct
            finish_bitfield(&off, &bitoff);
            off += compute_padding(off, fieldtype->align);
            squash_unnamed_struct(r, fieldtype, off);
            off += fieldtype->size;
            continue;
        }
        if (fieldtype->bitsize == 0) {
            // C11 6.7.2.1p12: The zero-size bit-field indicates the end of the
            // current run of the bit-fields.
            finish_bitfield(&off, &bitoff);
            off += compute_padding(off, fieldtype->align);
            bitoff = 0;
            continue;
        }
        if (fieldtype->bitsize > 0) {
            int bit = fieldtype->size * 8;
            int room = bit - (off * 8 + bitoff) % bit;
            if (fieldtype->bitsize <= room) {
                fieldtype->offset = off;
                fieldtype->bitoff = bitoff;
            } else {
                finish_bitfield(&off, &bitoff);
                off += compute_padding(off, fieldtype->align);
                fieldtype->offset = off;
                fieldtype->bitoff = 0;
            }
            bitoff += fieldtype->bitsize;
        } else {
            finish_bitfield(&off, &bitoff);
            off += compute_padding(off, fieldtype->align);
            fieldtype->offset = off;
            off += fieldtype->size;
        }
        if (name)
            dict_put(r, name, fieldtype);
    }
    finish_bitfield(&off, &bitoff);
    *rsize = off + compute_padding(off, *align);
    return r;
}