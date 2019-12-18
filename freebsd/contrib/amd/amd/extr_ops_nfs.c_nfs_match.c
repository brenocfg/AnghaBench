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
struct TYPE_3__ {scalar_t__ opt_fs; scalar_t__ opt_rfs; scalar_t__ opt_rhost; } ;
typedef  TYPE_1__ am_opts ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  dlog (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int strlen (scalar_t__) ; 
 scalar_t__ xmalloc (size_t) ; 
 int /*<<< orphan*/  xsnprintf (char*,size_t,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static char *
nfs_match(am_opts *fo)
{
  char *xmtab;
  size_t l;

  if (fo->opt_fs && !fo->opt_rfs)
    fo->opt_rfs = fo->opt_fs;
  if (!fo->opt_rfs) {
    plog(XLOG_USER, "nfs: no remote filesystem specified");
    return NULL;
  }
  if (!fo->opt_rhost) {
    plog(XLOG_USER, "nfs: no remote host specified");
    return NULL;
  }

  /*
   * Determine magic cookie to put in mtab
   */
  l = strlen(fo->opt_rhost) + strlen(fo->opt_rfs) + 2;
  xmtab = (char *) xmalloc(l);
  xsnprintf(xmtab, l, "%s:%s", fo->opt_rhost, fo->opt_rfs);
  dlog("NFS: mounting remote server \"%s\", remote fs \"%s\" on \"%s\"",
       fo->opt_rhost, fo->opt_rfs, fo->opt_fs);

  return xmtab;
}