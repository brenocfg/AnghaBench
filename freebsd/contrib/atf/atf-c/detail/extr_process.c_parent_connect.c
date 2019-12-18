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
struct TYPE_3__ {int* m_pipefds; int /*<<< orphan*/  m_sb; } ;
typedef  TYPE_1__ stream_prepare_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNREACHABLE ; 
 int atf_process_stream_type (int /*<<< orphan*/ ) ; 
 int const atf_process_stream_type_capture ; 
 int const atf_process_stream_type_connect ; 
 int const atf_process_stream_type_inherit ; 
 int const atf_process_stream_type_redirect_fd ; 
 int const atf_process_stream_type_redirect_path ; 
 int /*<<< orphan*/  close (int) ; 

__attribute__((used)) static
void
parent_connect(const stream_prepare_t *sp, int *fd)
{
    const int type = atf_process_stream_type(sp->m_sb);

    if (type == atf_process_stream_type_capture) {
        close(sp->m_pipefds[1]);
        *fd = sp->m_pipefds[0];
    } else if (type == atf_process_stream_type_connect) {
        /* Do nothing. */
    } else if (type == atf_process_stream_type_inherit) {
        /* Do nothing. */
    } else if (type == atf_process_stream_type_redirect_fd) {
        /* Do nothing. */
    } else if (type == atf_process_stream_type_redirect_path) {
        /* Do nothing. */
    } else {
        UNREACHABLE;
    }
}