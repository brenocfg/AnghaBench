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
typedef  int /*<<< orphan*/  atf_fs_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_exists (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static
bool
exists(const char *p)
{
    bool b;
    atf_fs_path_t pp;

    RE(atf_fs_path_init_fmt(&pp, "%s", p));
    RE(atf_fs_exists(&pp, &b));
    atf_fs_path_fini(&pp);

    return b;
}