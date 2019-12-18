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
struct map_entry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  m_listiter; struct map_entry const* m_entry; } ;
typedef  TYPE_1__ atf_map_citer_t ;

/* Variables and functions */
 scalar_t__ atf_list_citer_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_citer_next (int /*<<< orphan*/ ) ; 

atf_map_citer_t
atf_map_citer_next(const atf_map_citer_t citer)
{
    atf_map_citer_t newciter;

    newciter = citer;
    newciter.m_listiter = atf_list_citer_next(citer.m_listiter);
    newciter.m_entry = ((const struct map_entry *)
                        atf_list_citer_data(newciter.m_listiter));

    return newciter;
}