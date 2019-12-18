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
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_path_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*,char const*) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static
void
create_ctl_file(const char *name)
{
    atf_fs_path_t p;

    RE(atf_fs_path_init_fmt(&p, "%s", name));
    ATF_REQUIRE(open(atf_fs_path_cstring(&p),
                   O_CREAT | O_WRONLY | O_TRUNC, 0644) != -1);
    atf_fs_path_fini(&p);
}