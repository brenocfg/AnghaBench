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
struct TYPE_4__ {int /*<<< orphan*/  m_data; } ;
typedef  TYPE_1__ atf_fs_path_t ;

/* Variables and functions */
 int atf_equal_dynstr_dynstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool atf_equal_fs_path_fs_path(const atf_fs_path_t *p1,
                               const atf_fs_path_t *p2)
{
    return atf_equal_dynstr_dynstr(&p1->m_data, &p2->m_data);
}