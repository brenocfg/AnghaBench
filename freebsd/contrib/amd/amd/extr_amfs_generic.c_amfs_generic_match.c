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
struct TYPE_3__ {char* opt_rfs; char* opt_fs; } ;
typedef  TYPE_1__ am_opts ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 char* xstrdup (char*) ; 

char *
amfs_generic_match(am_opts *fo)
{
  char *p;

  if (!fo->opt_rfs) {
    plog(XLOG_USER, "amfs_generic_match: no mount point named (rfs:=)");
    return 0;
  }
  if (!fo->opt_fs) {
    plog(XLOG_USER, "amfs_generic_match: no map named (fs:=)");
    return 0;
  }

  /*
   * Swap round fs:= and rfs:= options
   * ... historical (jsp)
   */
  p = fo->opt_rfs;
  fo->opt_rfs = fo->opt_fs;
  fo->opt_fs = p;

  /*
   * mtab entry turns out to be the name of the mount map
   */
  return xstrdup(fo->opt_rfs ? fo->opt_rfs : ".");
}