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
struct redirect_path_stream {int /*<<< orphan*/  m_path; TYPE_1__ m_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  atf_process_stream_init_redirect_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  stderr_type 129 
#define  stdout_type 128 

__attribute__((used)) static
void
redirect_path_stream_init(void *v)
{
    struct redirect_path_stream *s = v;

    switch (s->m_base.m_type) {
    case stdout_type:
        RE(atf_fs_path_init_fmt(&s->m_path, "stdout"));
        break;
    case stderr_type:
        RE(atf_fs_path_init_fmt(&s->m_path, "stderr"));
        break;
    default:
        UNREACHABLE;
    }

    s->m_base.m_sb_ptr = &s->m_base.m_sb;
    RE(atf_process_stream_init_redirect_path(&s->m_base.m_sb, &s->m_path));
}