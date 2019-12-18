#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_2__ {scalar_t__ kind; } ;

/* Variables and functions */
 scalar_t__ TEOF ; 
 scalar_t__ is_funcdef () ; 
 int /*<<< orphan*/ * make_vector () ; 
 TYPE_1__* peek () ; 
 int /*<<< orphan*/  read_decl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_funcdef () ; 
 int /*<<< orphan*/ * toplevels ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Vector *read_toplevels() {
    toplevels = make_vector();
    for (;;) {
        if (peek()->kind == TEOF)
            return toplevels;
        if (is_funcdef())
            vec_push(toplevels, read_funcdef());
        else
            read_decl(toplevels, true);
    }
}