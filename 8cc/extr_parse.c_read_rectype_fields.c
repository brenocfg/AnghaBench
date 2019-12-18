#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
typedef  int /*<<< orphan*/  Dict ;

/* Variables and functions */
 int /*<<< orphan*/  fix_rectype_flexible_member (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_token (char) ; 
 int /*<<< orphan*/ * read_rectype_fields_sub () ; 
 int /*<<< orphan*/ * update_struct_offset (int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * update_union_offset (int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Dict *read_rectype_fields(int *rsize, int *align, bool is_struct) {
    if (!next_token('{'))
        return NULL;
    Vector *fields = read_rectype_fields_sub();
    fix_rectype_flexible_member(fields);
    if (is_struct)
        return update_struct_offset(rsize, align, fields);
    return update_union_offset(rsize, align, fields);
}