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
struct TYPE_3__ {char* opt_rfs; char* opt_sublink; char* opt_fs; int /*<<< orphan*/  opt_rhost; } ;
typedef  TYPE_1__ am_opts ;

/* Variables and functions */
 char* FALSE ; 
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  deslashify (char*) ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 char* str3cat (char*,int /*<<< orphan*/ ,char*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 char* strnsave (char*,int) ; 
 char* xrealloc (char*,int) ; 

__attribute__((used)) static char *
amfs_nfsx_match(am_opts *fo)
{
  char *xmtab;
  char *ptr;
  int len;

  if (!fo->opt_rfs) {
    plog(XLOG_USER, "amfs_nfsx: no remote filesystem specified");
    return FALSE;
  }

  if (!fo->opt_rhost) {
    plog(XLOG_USER, "amfs_nfsx: no remote host specified");
    return FALSE;
  }

  /* set default sublink */
  if (fo->opt_sublink == NULL || fo->opt_sublink[0] == '\0') {
    ptr = strchr(fo->opt_rfs, ',');
    if (ptr && ptr > (fo->opt_rfs + 1))
      fo->opt_sublink = strnsave(fo->opt_rfs + 1, ptr - fo->opt_rfs - 1);
  }

  /*
   * Remove trailing ",..." from ${fs}
   * After deslashifying, overwrite the end of ${fs} with "/"
   * to make sure it is unique.
   */
  if ((ptr = strchr(fo->opt_fs, ',')))
    *ptr = '\0';
  deslashify(fo->opt_fs);

  /*
   * Bump string length to allow trailing /
   */
  len = strlen(fo->opt_fs);
  fo->opt_fs = xrealloc(fo->opt_fs, len + 1 + 1);
  ptr = fo->opt_fs + len;

  /*
   * Make unique...
   */
  *ptr++ = '/';
  *ptr = '\0';

  /*
   * Determine magic cookie to put in mtab
   */
  xmtab = str3cat((char *) NULL, fo->opt_rhost, ":", fo->opt_rfs);
  dlog("NFSX: mounting remote server \"%s\", remote fs \"%s\" on \"%s\"",
       fo->opt_rhost, fo->opt_rfs, fo->opt_fs);

  return xmtab;
}