#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct params {int /*<<< orphan*/ * m_tcname; int /*<<< orphan*/  m_srcdir; int /*<<< orphan*/  m_resfile; int /*<<< orphan*/  m_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_map_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void
params_fini(struct params *p)
{
    atf_map_fini(&p->m_config);
    atf_fs_path_fini(&p->m_resfile);
    atf_fs_path_fini(&p->m_srcdir);
    if (p->m_tcname != NULL)
        free(p->m_tcname);
}