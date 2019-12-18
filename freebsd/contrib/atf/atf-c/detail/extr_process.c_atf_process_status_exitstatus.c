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
struct TYPE_4__ {int m_status; } ;
typedef  TYPE_1__ atf_process_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  atf_process_status_exited (TYPE_1__ const*) ; 

int
atf_process_status_exitstatus(const atf_process_status_t *s)
{
    PRE(atf_process_status_exited(s));
    int mutable_status = s->m_status;
    return WEXITSTATUS(mutable_status);
}