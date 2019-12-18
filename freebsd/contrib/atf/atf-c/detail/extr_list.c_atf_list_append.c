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
struct list_entry {struct list_entry* m_prev; } ;
struct TYPE_3__ {int /*<<< orphan*/  m_size; scalar_t__ m_end; } ;
typedef  TYPE_1__ atf_list_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 struct list_entry* new_entry_and_link (void*,int,struct list_entry*,struct list_entry*) ; 

atf_error_t
atf_list_append(atf_list_t *l, void *data, bool managed)
{
    struct list_entry *le, *next, *prev;
    atf_error_t err;

    next = (struct list_entry *)l->m_end;
    prev = next->m_prev;
    le = new_entry_and_link(data, managed, prev, next);
    if (le == NULL)
        err = atf_no_memory_error();
    else {
        l->m_size++;
        err = atf_no_error();
    }

    return err;
}