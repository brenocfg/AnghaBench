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
struct list_entry {void* m_object; } ;
struct TYPE_3__ {struct list_entry* m_entry; } ;
typedef  TYPE_1__ atf_list_iter_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 

void *
atf_list_iter_data(const atf_list_iter_t iter)
{
    const struct list_entry *le = iter.m_entry;
    PRE(le != NULL);
    return le->m_object;
}