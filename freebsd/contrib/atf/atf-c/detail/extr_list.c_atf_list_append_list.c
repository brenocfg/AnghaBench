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
struct list_entry {struct list_entry* m_prev; struct list_entry* m_next; } ;
struct TYPE_4__ {scalar_t__ m_size; scalar_t__ m_end; scalar_t__ m_begin; } ;
typedef  TYPE_1__ atf_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  delete_entry (struct list_entry*) ; 

void
atf_list_append_list(atf_list_t *l, atf_list_t *src)
{
    struct list_entry *e1, *e2, *ghost1, *ghost2;

    ghost1 = (struct list_entry *)l->m_end;
    ghost2 = (struct list_entry *)src->m_begin;

    e1 = ghost1->m_prev;
    e2 = ghost2->m_next;

    delete_entry(ghost1);
    delete_entry(ghost2);

    e1->m_next = e2;
    e2->m_prev = e1;

    l->m_end = src->m_end;
    l->m_size += src->m_size;
}