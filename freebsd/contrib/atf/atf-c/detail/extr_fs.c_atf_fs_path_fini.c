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
struct TYPE_3__ {int /*<<< orphan*/  m_data; } ;
typedef  TYPE_1__ atf_fs_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_dynstr_fini (int /*<<< orphan*/ *) ; 

void
atf_fs_path_fini(atf_fs_path_t *p)
{
    atf_dynstr_fini(&p->m_data);
}