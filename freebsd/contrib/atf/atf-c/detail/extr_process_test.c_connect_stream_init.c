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
struct connect_stream {int m_fd; TYPE_1__ m_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int STDERR_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  atf_process_stream_init_connect (int /*<<< orphan*/ *,int,int) ; 
 void* open (char*,int,int) ; 
#define  stderr_type 129 
#define  stdout_type 128 

__attribute__((used)) static
void
connect_stream_init(void *v)
{
    struct connect_stream *s = v;
    int src_fd;

    switch (s->m_base.m_type) {
    case stdout_type:
        src_fd = STDOUT_FILENO;
        s->m_fd = open("stdout", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        break;
    case stderr_type:
        src_fd = STDERR_FILENO;
        s->m_fd = open("stderr", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        break;
    default:
        UNREACHABLE;
        src_fd = -1;
    }
    ATF_REQUIRE(s->m_fd != -1);

    s->m_base.m_sb_ptr = &s->m_base.m_sb;
    RE(atf_process_stream_init_connect(&s->m_base.m_sb, src_fd, s->m_fd));
}