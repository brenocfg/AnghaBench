#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pimpl; } ;
typedef  TYPE_2__ atf_check_result_t ;
struct TYPE_4__ {int /*<<< orphan*/  m_stdout; } ;

/* Variables and functions */
 char const* atf_fs_path_cstring (int /*<<< orphan*/ *) ; 

const char *
atf_check_result_stdout(const atf_check_result_t *r)
{
    return atf_fs_path_cstring(&r->pimpl->m_stdout);
}