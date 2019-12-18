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
typedef  TYPE_2__ atf_tp_t ;
typedef  int /*<<< orphan*/  atf_tc_t ;
typedef  int /*<<< orphan*/  atf_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  m_tcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  POST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atf_tc_get_ident (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_tc (TYPE_2__*,int /*<<< orphan*/ ) ; 

atf_error_t
atf_tp_add_tc(atf_tp_t *tp, atf_tc_t *tc)
{
    atf_error_t err;

    PRE(find_tc(tp, atf_tc_get_ident(tc)) == NULL);

    err = atf_list_append(&tp->pimpl->m_tcs, tc, false);

    POST(find_tc(tp, atf_tc_get_ident(tc)) != NULL);

    return err;
}