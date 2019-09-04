#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* next; } ;
struct TYPE_7__ {struct TYPE_7__** child; struct TYPE_7__* next; TYPE_1__ versions; } ;
typedef  TYPE_2__ CheckasmFuncVersion ;
typedef  TYPE_2__ CheckasmFunc ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void destroy_func_tree(CheckasmFunc *f)
{
    if (f) {
        CheckasmFuncVersion *v = f->versions.next;
        while (v) {
            CheckasmFuncVersion *next = v->next;
            free(v);
            v = next;
        }

        destroy_func_tree(f->child[0]);
        destroy_func_tree(f->child[1]);
        free(f);
    }
}