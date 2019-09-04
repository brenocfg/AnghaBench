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
typedef  int /*<<< orphan*/  list ;
struct TYPE_4__ {char* key; char* val; scalar_t__ used; } ;
typedef  TYPE_1__ kvp ;

/* Variables and functions */
 int /*<<< orphan*/  list_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 

void option_insert(list *l, char *key, char *val)
{
    kvp *p = malloc(sizeof(kvp));
    p->key = key;
    p->val = val;
    p->used = 0;
    list_insert(l, p);
}