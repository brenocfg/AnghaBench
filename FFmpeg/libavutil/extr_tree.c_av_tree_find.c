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
struct TYPE_3__ {void const* elem; struct TYPE_3__** child; } ;
typedef  TYPE_1__ AVTreeNode ;

/* Variables and functions */

void *av_tree_find(const AVTreeNode *t, void *key,
                   int (*cmp)(const void *key, const void *b), void *next[2])
{
    if (t) {
        unsigned int v = cmp(key, t->elem);
        if (v) {
            if (next)
                next[v >> 31] = t->elem;
            return av_tree_find(t->child[(v >> 31) ^ 1], key, cmp, next);
        } else {
            if (next) {
                av_tree_find(t->child[0], key, cmp, next);
                av_tree_find(t->child[1], key, cmp, next);
            }
            return t->elem;
        }
    }
    return NULL;
}