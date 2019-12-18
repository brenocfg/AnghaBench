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
typedef  int /*<<< orphan*/  Token ;
struct TYPE_3__ {int nargs; scalar_t__ is_varg; } ;
typedef  TYPE_1__ Macro ;

/* Variables and functions */
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/ * read_one_arg (int /*<<< orphan*/ *,int*,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Vector *do_read_args(Token *ident, Macro *macro) {
    Vector *r = make_vector();
    bool end = false;
    while (!end) {
        bool in_ellipsis = (macro->is_varg && vec_len(r) + 1 == macro->nargs);
        vec_push(r, read_one_arg(ident, &end, in_ellipsis));
    }
    if (macro->is_varg && vec_len(r) == macro->nargs - 1)
        vec_push(r, make_vector());
    return r;
}