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
struct TYPE_7__ {void* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_8__ {scalar_t__ (* match ) (void*,void*) ;} ;
typedef  TYPE_2__ list ;

/* Variables and functions */
 int /*<<< orphan*/  AL_START_HEAD ; 
 int /*<<< orphan*/ * listGetIterator (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (void*,void*) ; 

listNode *listSearchKey(list *list, void *key)
{
    listIter *iter;
    listNode *node;

    iter = listGetIterator(list, AL_START_HEAD);
    while((node = listNext(iter)) != NULL) {
        if (list->match) {
            if (list->match(node->value, key)) {
                listReleaseIterator(iter);
                return node;
            }
        } else {
            if (key == node->value) {
                listReleaseIterator(iter);
                return node;
            }
        }
    }
    listReleaseIterator(iter);
    return NULL;
}