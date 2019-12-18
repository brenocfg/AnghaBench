#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* last_added_dialogue; int /*<<< orphan*/  cache_size; TYPE_1__* dialogue_cache; } ;
struct TYPE_5__ {scalar_t__ readorder; struct TYPE_5__* next; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ DialogueLine ;
typedef  TYPE_2__ ASSContext ;

/* Variables and functions */

__attribute__((used)) static void insert_dialogue(ASSContext *ass, DialogueLine *dialogue)
{
    DialogueLine *cur, *next = NULL, *prev = NULL;

    /* from the last added to the end of the list */
    if (ass->last_added_dialogue) {
        for (cur = ass->last_added_dialogue; cur; cur = cur->next) {
            if (cur->readorder > dialogue->readorder)
                break;
            prev = cur;
            next = cur->next;
        }
    }

    /* from the beginning to the last one added */
    if (!prev) {
        next = ass->dialogue_cache;
        for (cur = next; cur != ass->last_added_dialogue; cur = cur->next) {
            if (cur->readorder > dialogue->readorder)
                break;
            prev = cur;
            next = cur->next;
        }
    }

    if (prev) {
        prev->next = dialogue;
        dialogue->prev = prev;
    } else {
        dialogue->prev = ass->dialogue_cache;
        ass->dialogue_cache = dialogue;
    }
    if (next) {
        next->prev = dialogue;
        dialogue->next = next;
    }
    ass->cache_size++;
    ass->last_added_dialogue = dialogue;
}