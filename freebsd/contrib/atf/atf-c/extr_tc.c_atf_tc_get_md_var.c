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
struct TYPE_6__ {TYPE_1__* pimpl; } ;
typedef  TYPE_2__ atf_tc_t ;
typedef  int /*<<< orphan*/  atf_map_citer_t ;
struct TYPE_5__ {int /*<<< orphan*/  m_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 char* atf_map_citer_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_map_find_c (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  atf_tc_has_md_var (TYPE_2__ const*,char const*) ; 

const char *
atf_tc_get_md_var(const atf_tc_t *tc, const char *name)
{
    const char *val;
    atf_map_citer_t iter;

    PRE(atf_tc_has_md_var(tc, name));
    iter = atf_map_find_c(&tc->pimpl->m_vars, name);
    val = atf_map_citer_data(iter);
    INV(val != NULL);

    return val;
}