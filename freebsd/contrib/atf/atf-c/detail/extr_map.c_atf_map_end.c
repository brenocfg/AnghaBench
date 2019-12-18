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
struct TYPE_5__ {int /*<<< orphan*/  m_list; } ;
typedef  TYPE_1__ atf_map_t ;
struct TYPE_6__ {int /*<<< orphan*/  m_listiter; int /*<<< orphan*/ * m_entry; TYPE_1__* m_map; } ;
typedef  TYPE_2__ atf_map_iter_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_list_end (int /*<<< orphan*/ *) ; 

atf_map_iter_t
atf_map_end(atf_map_t *m)
{
    atf_map_iter_t iter;
    iter.m_map = m;
    iter.m_entry = NULL;
    iter.m_listiter = atf_list_end(&m->m_list);
    return iter;
}