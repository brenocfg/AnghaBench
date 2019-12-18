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
struct map_entry {void* m_value; } ;
struct TYPE_3__ {struct map_entry* m_entry; } ;
typedef  TYPE_1__ atf_map_iter_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 

void *
atf_map_iter_data(const atf_map_iter_t iter)
{
    const struct map_entry *me = iter.m_entry;
    PRE(me != NULL);
    return me->m_value;
}