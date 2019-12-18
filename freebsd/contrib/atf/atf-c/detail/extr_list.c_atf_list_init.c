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
struct list_entry {struct list_entry* m_prev; struct list_entry* m_next; } ;
struct TYPE_3__ {struct list_entry* m_end; struct list_entry* m_begin; scalar_t__ m_size; } ;
typedef  TYPE_1__ atf_list_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 int /*<<< orphan*/  free (struct list_entry*) ; 
 struct list_entry* new_entry (int /*<<< orphan*/ *,int) ; 

atf_error_t
atf_list_init(atf_list_t *l)
{
    struct list_entry *lebeg, *leend;

    lebeg = new_entry(NULL, false);
    if (lebeg == NULL) {
        return atf_no_memory_error();
    }

    leend = new_entry(NULL, false);
    if (leend == NULL) {
        free(lebeg);
        return atf_no_memory_error();
    }

    lebeg->m_next = leend;
    lebeg->m_prev = NULL;

    leend->m_next = NULL;
    leend->m_prev = lebeg;

    l->m_size = 0;
    l->m_begin = lebeg;
    l->m_end = leend;

    return atf_no_error();
}