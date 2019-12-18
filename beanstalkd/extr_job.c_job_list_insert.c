#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* prev; struct TYPE_5__* next; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  job_list_is_empty (TYPE_1__*) ; 

void
job_list_insert(Job *head, Job *j)
{
    if (!job_list_is_empty(j)) return; /* already in a linked list */

    j->prev = head->prev;
    j->next = head;
    head->prev->next = j;
    head->prev = j;
}