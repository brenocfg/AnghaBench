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
struct TYPE_2__ {int m_type; int /*<<< orphan*/  m_sb; } ;
struct capture_stream {TYPE_1__ m_base; int /*<<< orphan*/  m_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK (int) ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  atf_process_stream_fini (int /*<<< orphan*/ *) ; 
 int atf_utils_grep_string (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
#define  stderr_type 129 
#define  stdout_type 128 

__attribute__((used)) static
void
capture_stream_fini(void *v)
{
    struct capture_stream *s = v;

    switch (s->m_base.m_type) {
    case stdout_type:
        ATF_CHECK(atf_utils_grep_string("stdout: msg", s->m_msg));
        ATF_CHECK(!atf_utils_grep_string("stderr: msg", s->m_msg));
        break;
    case stderr_type:
        ATF_CHECK(!atf_utils_grep_string("stdout: msg", s->m_msg));
        ATF_CHECK(atf_utils_grep_string("stderr: msg", s->m_msg));
        break;
    default:
        UNREACHABLE;
    }

    free(s->m_msg);
    atf_process_stream_fini(&s->m_base.m_sb);
}