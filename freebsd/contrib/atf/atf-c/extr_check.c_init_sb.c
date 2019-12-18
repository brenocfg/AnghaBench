#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  atf_process_stream_t ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_process_stream_init_inherit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_process_stream_init_redirect_path (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static
atf_error_t
init_sb(const atf_fs_path_t *path, atf_process_stream_t *sb)
{
    atf_error_t err;

    if (path == NULL)
        err = atf_process_stream_init_inherit(sb);
    else
        err = atf_process_stream_init_redirect_path(sb, path);

    return err;
}