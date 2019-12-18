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
struct inherit_stream {int m_old_fd; int /*<<< orphan*/  m_fd; TYPE_1__ m_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  atf_process_stream_init_inherit (int /*<<< orphan*/ *) ; 
 int close (int /*<<< orphan*/ ) ; 
 int dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open (char const*,int,int) ; 
#define  stderr_type 129 
#define  stdout_type 128 

__attribute__((used)) static
void
inherit_stream_init(void *v)
{
    struct inherit_stream *s = v;
    const char *name;

    s->m_base.m_sb_ptr = &s->m_base.m_sb;
    RE(atf_process_stream_init_inherit(&s->m_base.m_sb));

    switch (s->m_base.m_type) {
    case stdout_type:
        s->m_fd = STDOUT_FILENO;
        name = "stdout";
        break;
    case stderr_type:
        s->m_fd = STDERR_FILENO;
        name = "stderr";
        break;
    default:
        UNREACHABLE;
        name = NULL;
    }

    s->m_old_fd = dup(s->m_fd);
    ATF_REQUIRE(s->m_old_fd != -1);
    ATF_REQUIRE(close(s->m_fd) != -1);
    ATF_REQUIRE_EQ(open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644),
                   s->m_fd);
}