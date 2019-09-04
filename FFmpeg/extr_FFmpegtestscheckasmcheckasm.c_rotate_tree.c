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
struct TYPE_4__ {scalar_t__ color; struct TYPE_4__** child; } ;
typedef  TYPE_1__ CheckasmFunc ;

/* Variables and functions */

__attribute__((used)) static CheckasmFunc *rotate_tree(CheckasmFunc *f, int dir)
{
    CheckasmFunc *r = f->child[dir^1];
    f->child[dir^1] = r->child[dir];
    r->child[dir] = f;
    r->color = f->color;
    f->color = 0;
    return r;
}