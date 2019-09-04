#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; scalar_t__ val; } ;
typedef  TYPE_1__ node ;
struct TYPE_6__ {TYPE_1__* front; } ;
typedef  TYPE_2__ list ;
struct TYPE_7__ {int used; char* val; int /*<<< orphan*/  key; } ;
typedef  TYPE_3__ kvp ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

char *option_find(list *l, char *key)
{
    node *n = l->front;
    while(n){
        kvp *p = (kvp *)n->val;
        if(strcmp(p->key, key) == 0){
            p->used = 1;
            return p->val;
        }
        n = n->next;
    }
    return 0;
}