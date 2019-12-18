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
struct list_entry {struct list_entry* m_prev; struct list_entry* m_next; } ;

/* Variables and functions */
 struct list_entry* new_entry (void*,int) ; 

__attribute__((used)) static
struct list_entry *
new_entry_and_link(void *object, bool managed, struct list_entry *prev,
                   struct list_entry *next)
{
    struct list_entry *le;

    le = new_entry(object, managed);
    if (le != NULL) {
        le->m_prev = prev;
        le->m_next = next;

        prev->m_next = le;
        next->m_prev = le;
    }

    return le;
}