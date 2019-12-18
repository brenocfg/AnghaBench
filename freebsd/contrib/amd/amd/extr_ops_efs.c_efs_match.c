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
struct TYPE_3__ {int /*<<< orphan*/  opt_dev; int /*<<< orphan*/  opt_fs; } ;
typedef  TYPE_1__ am_opts ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
efs_match(am_opts *fo)
{

  if (!fo->opt_dev) {
    plog(XLOG_USER, "efs: no device specified");
    return 0;
  }

  dlog("EFS: mounting device \"%s\" on \"%s\"", fo->opt_dev, fo->opt_fs);

  /*
   * Determine magic cookie to put in mtab
   */
  return xstrdup(fo->opt_dev);
}