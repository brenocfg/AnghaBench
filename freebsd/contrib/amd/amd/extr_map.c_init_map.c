#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  nt_seconds; } ;
struct TYPE_13__ {int na_fsid; TYPE_8__ na_atime; TYPE_8__ na_ctime; TYPE_8__ na_mtime; int /*<<< orphan*/  na_fileid; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_mtime; } ;
struct TYPE_9__ {int /*<<< orphan*/  ns_status; } ;
struct TYPE_11__ {int am_dev; int am_rdev; int* am_fd; TYPE_7__ am_fattr; TYPE_2__ am_stats; int /*<<< orphan*/  am_gen; TYPE_1__ am_attr; int /*<<< orphan*/  am_timeo; int /*<<< orphan*/ * am_autofs_fh; void* am_path; void* am_name; int /*<<< orphan*/ * am_alarray; int /*<<< orphan*/  am_al; } ;
typedef  TYPE_3__ am_node ;
struct TYPE_12__ {int /*<<< orphan*/  am_timeo; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_OK ; 
 int /*<<< orphan*/  clocktime (TYPE_8__*) ; 
 TYPE_7__ gen_fattr ; 
 TYPE_6__ gopt ; 
 int /*<<< orphan*/  new_gen () ; 
 int /*<<< orphan*/  new_loc () ; 
 int /*<<< orphan*/  new_ttl (TYPE_3__*) ; 
 void* xstrdup (char*) ; 

void
init_map(am_node *mp, char *dir)
{
  /*
   * mp->am_mapno is initialized by exported_ap_alloc
   * other fields don't need to be set to zero.
   */

  mp->am_al = new_loc();
  mp->am_alarray = NULL;
  mp->am_name = xstrdup(dir);
  mp->am_path = xstrdup(dir);
  mp->am_gen = new_gen();
#ifdef HAVE_FS_AUTOFS
  mp->am_autofs_fh = NULL;
#endif /* HAVE_FS_AUTOFS */

  mp->am_timeo = gopt.am_timeo;
  mp->am_attr.ns_status = NFS_OK;
  mp->am_fattr = gen_fattr;
  mp->am_fattr.na_fsid = 42;
  mp->am_fattr.na_fileid = mp->am_gen;
  clocktime(&mp->am_fattr.na_atime);
  /* next line copies a "struct nfstime" among several fields */
  mp->am_fattr.na_mtime = mp->am_fattr.na_ctime = mp->am_fattr.na_atime;

  new_ttl(mp);
  mp->am_stats.s_mtime = mp->am_fattr.na_atime.nt_seconds;
  mp->am_dev = -1;
  mp->am_rdev = -1;
  mp->am_fd[0] = -1;
  mp->am_fd[1] = -1;
}