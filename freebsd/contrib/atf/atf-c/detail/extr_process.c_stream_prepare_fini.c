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
struct TYPE_3__ {int /*<<< orphan*/ * m_pipefds; scalar_t__ m_pipefds_ok; } ;
typedef  TYPE_1__ stream_prepare_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
stream_prepare_fini(stream_prepare_t *sp)
{
    if (sp->m_pipefds_ok) {
        close(sp->m_pipefds[0]);
        close(sp->m_pipefds[1]);
    }
}