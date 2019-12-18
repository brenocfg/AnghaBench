#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_10__ {scalar_t__ kind; int bitsize; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_PARAM_TYPEONLY ; 
 scalar_t__ KIND_STRUCT ; 
 char KSTATIC_ASSERT ; 
 TYPE_1__* copy_type (TYPE_1__*) ; 
 int /*<<< orphan*/  ensure_not_void (TYPE_1__*) ; 
 int /*<<< orphan*/  expect (char) ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  is_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_pair (char*,TYPE_1__*) ; 
 int /*<<< orphan*/ * make_vector () ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/  peek () ; 
 int read_bitsize (char*,TYPE_1__*) ; 
 TYPE_1__* read_decl_spec (int /*<<< orphan*/ *) ; 
 TYPE_1__* read_declarator (char**,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_static_assert () ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnt (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static Vector *read_rectype_fields_sub() {
    Vector *r = make_vector();
    for (;;) {
        if (next_token(KSTATIC_ASSERT)) {
            read_static_assert();
            continue;
        }
        if (!is_type(peek()))
            break;
        Type *basetype = read_decl_spec(NULL);
        if (basetype->kind == KIND_STRUCT && next_token(';')) {
            vec_push(r, make_pair(NULL, basetype));
            continue;
        }
        for (;;) {
            char *name = NULL;
            Type *fieldtype = read_declarator(&name, basetype, NULL, DECL_PARAM_TYPEONLY);
            ensure_not_void(fieldtype);
            fieldtype = copy_type(fieldtype);
            fieldtype->bitsize = next_token(':') ? read_bitsize(name, fieldtype) : -1;
            vec_push(r, make_pair(name, fieldtype));
            if (next_token(','))
                continue;
            if (is_keyword(peek(), '}'))
                warnt(peek(), "missing ';' at the end of field list");
            else
                expect(';');
            break;
        }
    }
    expect('}');
    return r;
}