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
struct TYPE_2__ {int /*<<< orphan*/  m_type; int /*<<< orphan*/  m_sb; } ;
struct redirect_fd_stream {TYPE_1__ m_base; int /*<<< orphan*/  m_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  atf_process_stream_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_file (int /*<<< orphan*/ ) ; 
 int close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
redirect_fd_stream_fini(void *v)
{
    struct redirect_fd_stream *s = v;

    ATF_REQUIRE(close(s->m_fd) != -1);

    atf_process_stream_fini(&s->m_base.m_sb);

    check_file(s->m_base.m_type);
}