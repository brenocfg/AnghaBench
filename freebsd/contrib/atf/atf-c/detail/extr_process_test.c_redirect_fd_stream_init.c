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
struct TYPE_2__ {int m_type; int /*<<< orphan*/  m_sb; int /*<<< orphan*/ * m_sb_ptr; } ;
struct redirect_fd_stream {int m_fd; TYPE_1__ m_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  atf_process_stream_init_redirect_fd (int /*<<< orphan*/ *,int) ; 
 void* open (char*,int,int) ; 
#define  stderr_type 129 
#define  stdout_type 128 

__attribute__((used)) static
void
redirect_fd_stream_init(void *v)
{
    struct redirect_fd_stream *s = v;

    switch (s->m_base.m_type) {
    case stdout_type:
        s->m_fd = open("stdout", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        break;
    case stderr_type:
        s->m_fd = open("stderr", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        break;
    default:
        UNREACHABLE;
    }
    ATF_REQUIRE(s->m_fd != -1);

    s->m_base.m_sb_ptr = &s->m_base.m_sb;
    RE(atf_process_stream_init_redirect_fd(&s->m_base.m_sb, s->m_fd));
}