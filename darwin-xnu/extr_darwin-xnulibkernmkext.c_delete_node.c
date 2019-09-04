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
struct encode_state {int* parent; int* rchild; int* lchild; } ;

/* Variables and functions */
 int NIL ; 

__attribute__((used)) static void delete_node(struct encode_state *sp, int p)
{
    int  q;
    
    if (sp->parent[p] == NIL)
        return;  /* not in tree */
    if (sp->rchild[p] == NIL)
        q = sp->lchild[p];
    else if (sp->lchild[p] == NIL)
        q = sp->rchild[p];
    else {
        q = sp->lchild[p];
        if (sp->rchild[q] != NIL) {
            do {
                q = sp->rchild[q];
            } while (sp->rchild[q] != NIL);
            sp->rchild[sp->parent[q]] = sp->lchild[q];
            sp->parent[sp->lchild[q]] = sp->parent[q];
            sp->lchild[q] = sp->lchild[p];
            sp->parent[sp->lchild[p]] = q;
        }
        sp->rchild[q] = sp->rchild[p];
        sp->parent[sp->rchild[p]] = q;
    }
    sp->parent[q] = sp->parent[p];
    if (sp->rchild[sp->parent[p]] == p)
        sp->rchild[sp->parent[p]] = q;
    else
        sp->lchild[sp->parent[p]] = q;
    sp->parent[p] = NIL;
}