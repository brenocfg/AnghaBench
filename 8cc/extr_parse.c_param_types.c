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
struct TYPE_3__ {int /*<<< orphan*/  ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int /*<<< orphan*/ * make_vector () ; 
 TYPE_1__* vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Vector *param_types(Vector *params) {
    Vector *r = make_vector();
    for (int i = 0; i < vec_len(params); i++) {
        Node *param = vec_get(params, i);
        vec_push(r, param->ty);
    }
    return r;
}