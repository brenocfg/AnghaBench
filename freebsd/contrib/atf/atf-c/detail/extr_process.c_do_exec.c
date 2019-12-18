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
struct exec_args {int /*<<< orphan*/  m_prog; int /*<<< orphan*/  m_argv; int /*<<< orphan*/  (* m_prehook ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  INV (int) ; 
 char* atf_fs_path_cstring (int /*<<< orphan*/ ) ; 
 int const_execvp (char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int const) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static
void
do_exec(void *v)
{
    struct exec_args *ea = v;

    if (ea->m_prehook != NULL)
        ea->m_prehook();

    const int ret = const_execvp(atf_fs_path_cstring(ea->m_prog), ea->m_argv);
    const int errnocopy = errno;
    INV(ret == -1);
    fprintf(stderr, "exec(%s) failed: %s\n",
            atf_fs_path_cstring(ea->m_prog), strerror(errnocopy));
    exit(EXIT_FAILURE);
}