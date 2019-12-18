#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  func; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; TYPE_1__ versions; struct TYPE_8__** child; } ;
typedef  TYPE_2__ CheckasmFunc ;

/* Variables and functions */
 int /*<<< orphan*/  balance_tree (TYPE_2__**) ; 
 TYPE_2__* checkasm_malloc (int) ; 
 int cmp_func_names (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static CheckasmFunc *get_func(CheckasmFunc **root, const char *name)
{
    CheckasmFunc *f = *root;

    if (f) {
        /* Search the tree for a matching node */
        int cmp = cmp_func_names(name, f->name);
        if (cmp) {
            f = get_func(&f->child[cmp > 0], name);

            /* Rebalance the tree on the way up if a new node was inserted */
            if (!f->versions.func)
                balance_tree(root);
        }
    } else {
        /* Allocate and insert a new node into the tree */
        int name_length = strlen(name);
        f = *root = checkasm_malloc(sizeof(CheckasmFunc) + name_length);
        memcpy(f->name, name, name_length + 1);
    }

    return f;
}