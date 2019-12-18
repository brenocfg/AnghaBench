#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  m_sb; int /*<<< orphan*/ * m_sb_ptr; } ;
struct capture_stream {int /*<<< orphan*/ * m_msg; TYPE_1__ m_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_process_stream_init_capture (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void
capture_stream_init(void *v)
{
    struct capture_stream *s = v;

    s->m_base.m_sb_ptr = &s->m_base.m_sb;
    RE(atf_process_stream_init_capture(&s->m_base.m_sb));
    s->m_msg = NULL;
}