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
struct TYPE_3__ {int m_stdout; int m_stderr; scalar_t__ m_pid; } ;
typedef  TYPE_1__ atf_process_child_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_no_error () ; 

__attribute__((used)) static
atf_error_t
atf_process_child_init(atf_process_child_t *c)
{
    c->m_pid = 0;
    c->m_stdout = -1;
    c->m_stderr = -1;

    return atf_no_error();
}