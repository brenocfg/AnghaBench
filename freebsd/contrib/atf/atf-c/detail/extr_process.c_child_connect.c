#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* m_pipefds; TYPE_3__* m_sb; } ;
typedef  TYPE_1__ stream_prepare_t ;
typedef  int /*<<< orphan*/  atf_error_t ;
struct TYPE_5__ {int m_fd; int /*<<< orphan*/  m_path; int /*<<< orphan*/  m_src_fd; int /*<<< orphan*/  m_tgt_fd; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  atf_fs_path_cstring (int /*<<< orphan*/ ) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_libc_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int atf_process_stream_type (TYPE_3__*) ; 
 int const atf_process_stream_type_capture ; 
 int const atf_process_stream_type_connect ; 
 int const atf_process_stream_type_inherit ; 
 int const atf_process_stream_type_redirect_fd ; 
 int const atf_process_stream_type_redirect_path ; 
 int /*<<< orphan*/  close (int) ; 
 int dup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  safe_dup (int,int) ; 

__attribute__((used)) static
atf_error_t
child_connect(const stream_prepare_t *sp, int procfd)
{
    atf_error_t err;
    const int type = atf_process_stream_type(sp->m_sb);

    if (type == atf_process_stream_type_capture) {
        close(sp->m_pipefds[0]);
        err = safe_dup(sp->m_pipefds[1], procfd);
    } else if (type == atf_process_stream_type_connect) {
        if (dup2(sp->m_sb->m_tgt_fd, sp->m_sb->m_src_fd) == -1)
            err = atf_libc_error(errno, "Cannot connect descriptor %d to %d",
                                 sp->m_sb->m_tgt_fd, sp->m_sb->m_src_fd);
        else
            err = atf_no_error();
    } else if (type == atf_process_stream_type_inherit) {
        err = atf_no_error();
    } else if (type == atf_process_stream_type_redirect_fd) {
        err = safe_dup(sp->m_sb->m_fd, procfd);
    } else if (type == atf_process_stream_type_redirect_path) {
        int aux = open(atf_fs_path_cstring(sp->m_sb->m_path),
                       O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (aux == -1)
            err = atf_libc_error(errno, "Could not create %s",
                                 atf_fs_path_cstring(sp->m_sb->m_path));
        else {
            err = safe_dup(aux, procfd);
            if (atf_is_error(err))
                close(aux);
        }
    } else {
        UNREACHABLE;
        err = atf_no_error();
    }

    return err;
}