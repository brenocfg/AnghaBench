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
struct list_entry {int dummy; } ;
typedef  int /*<<< orphan*/  atf_list_t ;
struct TYPE_3__ {struct list_entry const* m_entry; int /*<<< orphan*/  const* m_list; } ;
typedef  TYPE_1__ atf_list_citer_t ;

/* Variables and functions */

__attribute__((used)) static
atf_list_citer_t
entry_to_citer(const atf_list_t *l, const struct list_entry *le)
{
    atf_list_citer_t iter;
    iter.m_list = l;
    iter.m_entry = le;
    return iter;
}