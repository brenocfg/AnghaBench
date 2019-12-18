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
struct list_entry {struct list_entry* m_next; } ;
struct TYPE_4__ {struct list_entry* m_entry; } ;
typedef  TYPE_1__ atf_list_citer_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 

atf_list_citer_t
atf_list_citer_next(const atf_list_citer_t citer)
{
    const struct list_entry *le = citer.m_entry;
    atf_list_citer_t newciter;

    PRE(le != NULL);

    newciter = citer;
    newciter.m_entry = le->m_next;

    return newciter;
}