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

/* Variables and functions */
 int /*<<< orphan*/  UNREACHABLE ; 
 int const atf_fs_stat_blk_type ; 
 int const atf_fs_stat_chr_type ; 
 int const atf_fs_stat_dir_type ; 
 int const atf_fs_stat_fifo_type ; 
 int const atf_fs_stat_lnk_type ; 
 int const atf_fs_stat_reg_type ; 
 int const atf_fs_stat_sock_type ; 
 int const atf_fs_stat_wht_type ; 

__attribute__((used)) static
const char *
stat_type_to_string(const int type)
{
    const char *str;

    if (type == atf_fs_stat_blk_type)
        str = "block device";
    else if (type == atf_fs_stat_chr_type)
        str = "character device";
    else if (type == atf_fs_stat_dir_type)
        str = "directory";
    else if (type == atf_fs_stat_fifo_type)
        str = "named pipe";
    else if (type == atf_fs_stat_lnk_type)
        str = "symbolic link";
    else if (type == atf_fs_stat_reg_type)
        str = "regular file";
    else if (type == atf_fs_stat_sock_type)
        str = "socket";
    else if (type == atf_fs_stat_wht_type)
        str = "whiteout";
    else {
        UNREACHABLE;
        str = NULL;
    }

    return str;
}