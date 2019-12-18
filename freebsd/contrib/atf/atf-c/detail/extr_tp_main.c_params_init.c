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
struct params {int m_do_list; int /*<<< orphan*/  m_srcdir; int /*<<< orphan*/  m_resfile; int /*<<< orphan*/  m_config; int /*<<< orphan*/  m_tcpart; int /*<<< orphan*/ * m_tcname; } ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  BODY ; 
 int /*<<< orphan*/  argv0_to_dir (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_map_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
atf_error_t
params_init(struct params *p, const char *argv0)
{
    atf_error_t err;

    p->m_do_list = false;
    p->m_tcname = NULL;
    p->m_tcpart = BODY;

    err = argv0_to_dir(argv0, &p->m_srcdir);
    if (atf_is_error(err))
        return err;

    err = atf_fs_path_init_fmt(&p->m_resfile, "/dev/stdout");
    if (atf_is_error(err)) {
        atf_fs_path_fini(&p->m_srcdir);
        return err;
    }

    err = atf_map_init(&p->m_config);
    if (atf_is_error(err)) {
        atf_fs_path_fini(&p->m_resfile);
        atf_fs_path_fini(&p->m_srcdir);
        return err;
    }

    return err;
}