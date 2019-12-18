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
typedef  int /*<<< orphan*/  atf_process_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  m_pid; } ;
typedef  TYPE_1__ atf_process_child_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_libc_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_process_child_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  atf_process_status_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 
 int waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

atf_error_t
atf_process_child_wait(atf_process_child_t *c, atf_process_status_t *s)
{
    atf_error_t err;
    int status;

    if (waitpid(c->m_pid, &status, 0) == -1)
        err = atf_libc_error(errno, "Failed waiting for process %d",
                             c->m_pid);
    else {
        atf_process_child_fini(c);
        err = atf_process_status_init(s, status);
    }

    return err;
}