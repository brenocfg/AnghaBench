#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {scalar_t__ kind; int position; int /*<<< orphan*/ * hideset; scalar_t__ is_vararg; } ;
typedef  TYPE_1__ Vector ;
typedef  TYPE_1__ Token ;
struct TYPE_32__ {TYPE_1__* body; } ;
typedef  int /*<<< orphan*/  Set ;
typedef  TYPE_3__ Macro ;

/* Variables and functions */
 char KHASHHASH ; 
 scalar_t__ TMACRO_PARAM ; 
 TYPE_1__* add_hide_set (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* expand_all (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  glue_push (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ is_keyword (TYPE_1__*,char) ; 
 TYPE_1__* make_vector () ; 
 TYPE_1__* stringize (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vec_append (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* vec_get (TYPE_1__*,int) ; 
 TYPE_1__* vec_head (TYPE_1__*) ; 
 scalar_t__ vec_len (TYPE_1__*) ; 
 int /*<<< orphan*/  vec_pop (TYPE_1__*) ; 
 int /*<<< orphan*/  vec_push (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* vec_tail (TYPE_1__*) ; 

__attribute__((used)) static Vector *subst(Macro *macro, Vector *args, Set *hideset) {
    Vector *r = make_vector();
    int len = vec_len(macro->body);
    for (int i = 0; i < len; i++) {
        Token *t0 = vec_get(macro->body, i);
        Token *t1 = (i == len - 1) ? NULL : vec_get(macro->body, i + 1);
        bool t0_param = (t0->kind == TMACRO_PARAM);
        bool t1_param = (t1 && t1->kind == TMACRO_PARAM);

        if (is_keyword(t0, '#') && t1_param) {
            vec_push(r, stringize(t0, vec_get(args, t1->position)));
            i++;
            continue;
        }
        if (is_keyword(t0, KHASHHASH) && t1_param) {
            Vector *arg = vec_get(args, t1->position);
            // [GNU] [,##__VA_ARG__] is expanded to the empty token sequence
            // if __VA_ARG__ is empty. Otherwise it's expanded to
            // [,<tokens in __VA_ARG__>].
            if (t1->is_vararg && vec_len(r) > 0 && is_keyword(vec_tail(r), ',')) {
                if (vec_len(arg) > 0)
                    vec_append(r, arg);
                else
                    vec_pop(r);
            } else if (vec_len(arg) > 0) {
                glue_push(r, vec_head(arg));
                for (int i = 1; i < vec_len(arg); i++)
                    vec_push(r, vec_get(arg, i));
            }
            i++;
            continue;
        }
        if (is_keyword(t0, KHASHHASH) && t1) {
            hideset = t1->hideset;
            glue_push(r, t1);
            i++;
            continue;
        }
        if (t0_param && t1 && is_keyword(t1, KHASHHASH)) {
            hideset = t1->hideset;
            Vector *arg = vec_get(args, t0->position);
            if (vec_len(arg) == 0)
                i++;
            else
                vec_append(r, arg);
            continue;
        }
        if (t0_param) {
            Vector *arg = vec_get(args, t0->position);
            vec_append(r, expand_all(arg, t0));
            continue;
        }
        vec_push(r, t0);
    }
    return add_hide_set(r, hideset);
}