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
struct TYPE_3__ {int m_pipefds_ok; int /*<<< orphan*/  m_pipefds; int /*<<< orphan*/  const* m_sb; } ;
typedef  TYPE_1__ stream_prepare_t ;
typedef  int /*<<< orphan*/  atf_process_stream_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_libc_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int atf_process_stream_type (int /*<<< orphan*/  const*) ; 
 int const atf_process_stream_type_capture ; 
 int /*<<< orphan*/  errno ; 
 int pipe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
atf_error_t
stream_prepare_init(stream_prepare_t *sp, const atf_process_stream_t *sb)
{
    atf_error_t err;

    const int type = atf_process_stream_type(sb);

    sp->m_sb = sb;
    sp->m_pipefds_ok = false;

    if (type == atf_process_stream_type_capture) {
        if (pipe(sp->m_pipefds) == -1)
            err = atf_libc_error(errno, "Failed to create pipe");
        else {
            err = atf_no_error();
            sp->m_pipefds_ok = true;
        }
    } else
        err = atf_no_error();

    return err;
}