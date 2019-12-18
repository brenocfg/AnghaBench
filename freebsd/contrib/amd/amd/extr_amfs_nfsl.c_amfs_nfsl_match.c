#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_8__ {char* opt_rhost; char* opt_sublink; char* opt_fs; } ;
typedef  TYPE_1__ am_opts ;
struct TYPE_10__ {char* (* fs_match ) (TYPE_1__*) ;} ;
struct TYPE_9__ {char* (* fs_match ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  STRCEQ (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  am_get_hostname () ; 
 TYPE_7__ amfs_link_ops ; 
 int /*<<< orphan*/  hostd ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 TYPE_5__ nfs_ops ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 char* stub1 (TYPE_1__*) ; 
 char* stub2 (TYPE_1__*) ; 
 char* stub3 (TYPE_1__*) ; 

__attribute__((used)) static char *
amfs_nfsl_match(am_opts *fo)
{
  char *cp;
  char *ho = fo->opt_rhost;
  char *retval;
  struct stat stb;

  if (fo->opt_sublink && fo->opt_sublink[0])
    cp = fo->opt_sublink;
  else
    cp = fo->opt_fs;

  if (!cp || !ho) {
    plog(XLOG_USER, "amfs_nfsl: host $fs and $rhost must be specified");
    return NULL;
  }

  /*
   * If this host is not the same as $rhost, or if link does not exist,
   * call nfs_ops.fs_match().
   * If link value exists (or same host), call amfs_link_ops.fs_match().
   */
  if (!STRCEQ(ho, am_get_hostname()) && !STRCEQ(ho, hostd)) {
    plog(XLOG_INFO, "amfs_nfsl: \"%s\" is not the local host \"%s\", "
	"or \"%s\" using type:=nfs", ho, am_get_hostname(), hostd);
    retval = nfs_ops.fs_match(fo);
  } else if (lstat(cp, &stb) < 0) {
    plog(XLOG_INFO, "amfs_nfsl: \"%s\" does not exist, using type:=nfs", cp);
    retval = nfs_ops.fs_match(fo);
  } else {
    plog(XLOG_INFO, "amfs_nfsl: \"%s\" exists, using type:=link", cp);
    retval = amfs_link_ops.fs_match(fo);
  }
  return retval;
}