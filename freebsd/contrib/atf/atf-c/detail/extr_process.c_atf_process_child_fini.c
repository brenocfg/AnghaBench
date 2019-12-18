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
struct TYPE_3__ {int m_stdout; int m_stderr; } ;
typedef  TYPE_1__ atf_process_child_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 

__attribute__((used)) static
void
atf_process_child_fini(atf_process_child_t *c)
{
    if (c->m_stdout != -1)
        close(c->m_stdout);
    if (c->m_stderr != -1)
        close(c->m_stderr);
}