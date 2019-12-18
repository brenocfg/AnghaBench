#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int tv_nsec; } ;
struct TYPE_9__ {int tv_nsec; } ;
struct TYPE_8__ {int tv_nsec; } ;
struct TYPE_11__ {scalar_t__ st_ino; int st_atimensec; int st_atime_n; int st_mtimensec; int st_mtime_n; int st_ctimensec; int st_ctime_n; scalar_t__ st_blocks; TYPE_3__ st_ctim; int /*<<< orphan*/  st_ctime; TYPE_2__ st_mtim; int /*<<< orphan*/  st_mtime; TYPE_1__ st_atim; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_4__ struct_stat ;
typedef  void* apr_off_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;
typedef  scalar_t__ apr_ino_t ;
struct TYPE_12__ {int valid; scalar_t__ inode; int atime; int mtime; int ctime; void* csize; int /*<<< orphan*/  nlink; int /*<<< orphan*/  device; int /*<<< orphan*/  size; int /*<<< orphan*/  group; int /*<<< orphan*/  user; int /*<<< orphan*/  filetype; int /*<<< orphan*/  protection; } ;
typedef  TYPE_5__ apr_finfo_t ;

/* Variables and functions */
 int APR_FINFO_CSIZE ; 
 int APR_FINFO_IDENT ; 
 int APR_FINFO_INODE ; 
 int APR_FINFO_MIN ; 
 int APR_FINFO_NLINK ; 
 int APR_FINFO_OWNER ; 
 int APR_FINFO_PROT ; 
 int APR_TIME_C (int) ; 
 scalar_t__ DEV_BSIZE ; 
 int /*<<< orphan*/  apr_time_ansi_put (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_unix_mode2perms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filetype_from_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_out_finfo(apr_finfo_t *finfo, struct_stat *info,
                           apr_int32_t wanted)
{ 
    finfo->valid = APR_FINFO_MIN | APR_FINFO_IDENT | APR_FINFO_NLINK
                 | APR_FINFO_OWNER | APR_FINFO_PROT;
    finfo->protection = apr_unix_mode2perms(info->st_mode);
    finfo->filetype = filetype_from_mode(info->st_mode);
    finfo->user = info->st_uid;
    finfo->group = info->st_gid;
    finfo->size = info->st_size;
    finfo->device = info->st_dev;
    finfo->nlink = info->st_nlink;

    /* Check for overflow if storing a 64-bit st_ino in a 32-bit
     * apr_ino_t for LFS builds: */
    if (sizeof(apr_ino_t) >= sizeof(info->st_ino)
        || (apr_ino_t)info->st_ino == info->st_ino) {
        finfo->inode = info->st_ino;
    } else {
        finfo->valid &= ~APR_FINFO_INODE;
    }

    apr_time_ansi_put(&finfo->atime, info->st_atime);
#ifdef HAVE_STRUCT_STAT_ST_ATIM_TV_NSEC
    finfo->atime += info->st_atim.tv_nsec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_ATIMENSEC)
    finfo->atime += info->st_atimensec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_ATIME_N)
    finfo->atime += info->st_atime_n / APR_TIME_C(1000);
#endif

    apr_time_ansi_put(&finfo->mtime, info->st_mtime);
#ifdef HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC
    finfo->mtime += info->st_mtim.tv_nsec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_MTIMENSEC)
    finfo->mtime += info->st_mtimensec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_MTIME_N)
    finfo->mtime += info->st_mtime_n / APR_TIME_C(1000);
#endif

    apr_time_ansi_put(&finfo->ctime, info->st_ctime);
#ifdef HAVE_STRUCT_STAT_ST_CTIM_TV_NSEC
    finfo->ctime += info->st_ctim.tv_nsec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_CTIMENSEC)
    finfo->ctime += info->st_ctimensec / APR_TIME_C(1000);
#elif defined(HAVE_STRUCT_STAT_ST_CTIME_N)
    finfo->ctime += info->st_ctime_n / APR_TIME_C(1000);
#endif

#ifdef HAVE_STRUCT_STAT_ST_BLOCKS
#ifdef DEV_BSIZE
    finfo->csize = (apr_off_t)info->st_blocks * (apr_off_t)DEV_BSIZE;
#else
    finfo->csize = (apr_off_t)info->st_blocks * (apr_off_t)512;
#endif
    finfo->valid |= APR_FINFO_CSIZE;
#endif
}