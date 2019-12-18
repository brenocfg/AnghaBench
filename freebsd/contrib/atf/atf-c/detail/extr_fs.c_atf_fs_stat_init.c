#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int st_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  m_type; TYPE_2__ m_sb; } ;
typedef  TYPE_1__ atf_fs_stat_t ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
#define  S_IFBLK 135 
#define  S_IFCHR 134 
#define  S_IFDIR 133 
#define  S_IFIFO 132 
#define  S_IFLNK 131 
 int S_IFMT ; 
#define  S_IFREG 130 
#define  S_IFSOCK 129 
#define  S_IFWHT 128 
 char* atf_fs_path_cstring (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  atf_fs_stat_blk_type ; 
 int /*<<< orphan*/  atf_fs_stat_chr_type ; 
 int /*<<< orphan*/  atf_fs_stat_dir_type ; 
 int /*<<< orphan*/  atf_fs_stat_fifo_type ; 
 int /*<<< orphan*/  atf_fs_stat_lnk_type ; 
 int /*<<< orphan*/  atf_fs_stat_reg_type ; 
 int /*<<< orphan*/  atf_fs_stat_sock_type ; 
 int /*<<< orphan*/  atf_fs_stat_wht_type ; 
 int /*<<< orphan*/  atf_libc_error (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  errno ; 
 int lstat (char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  unknown_type_error (char const*,int) ; 

atf_error_t
atf_fs_stat_init(atf_fs_stat_t *st, const atf_fs_path_t *p)
{
    atf_error_t err;
    const char *pstr = atf_fs_path_cstring(p);

    if (lstat(pstr, &st->m_sb) == -1) {
        err = atf_libc_error(errno, "Cannot get information of %s; "
                             "lstat(2) failed", pstr);
    } else {
        int type = st->m_sb.st_mode & S_IFMT;
        err = atf_no_error();
        switch (type) {
            case S_IFBLK:  st->m_type = atf_fs_stat_blk_type;  break;
            case S_IFCHR:  st->m_type = atf_fs_stat_chr_type;  break;
            case S_IFDIR:  st->m_type = atf_fs_stat_dir_type;  break;
            case S_IFIFO:  st->m_type = atf_fs_stat_fifo_type; break;
            case S_IFLNK:  st->m_type = atf_fs_stat_lnk_type;  break;
            case S_IFREG:  st->m_type = atf_fs_stat_reg_type;  break;
            case S_IFSOCK: st->m_type = atf_fs_stat_sock_type; break;
#if defined(S_IFWHT)
            case S_IFWHT:  st->m_type = atf_fs_stat_wht_type;  break;
#endif
            default:
                err = unknown_type_error(pstr, type);
        }
    }

    return err;
}