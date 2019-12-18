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
typedef  int /*<<< orphan*/  atf_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* m_cleanup ) (TYPE_2__ const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*) ; 

atf_error_t
atf_tc_cleanup(const atf_tc_t *tc)
{
    if (tc->pimpl->m_cleanup != NULL)
        tc->pimpl->m_cleanup(tc);
    return atf_no_error(); /* XXX */
}