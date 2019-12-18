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
struct list_entry {void const* m_object; } ;
struct TYPE_3__ {struct list_entry* m_entry; } ;
typedef  TYPE_1__ atf_list_citer_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 

const void *
atf_list_citer_data(const atf_list_citer_t citer)
{
    const struct list_entry *le = citer.m_entry;
    PRE(le != NULL);
    return le->m_object;
}