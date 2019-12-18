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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {char* mt_directory; struct TYPE_3__* mt_child; struct TYPE_3__* mt_next; int /*<<< orphan*/  mt_mountpoint; } ;
typedef  TYPE_1__ amq_mount_tree ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 scalar_t__ NSTREQ (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STREQ (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrlcat (char*,char*,int) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void
show_pwd(amq_mount_tree *mt, char *path, size_t l, int *flag)
{
  int len;

  while (mt) {
    len = strlen(mt->mt_mountpoint);
    if (NSTREQ(path, mt->mt_mountpoint, len) &&
	!STREQ(mt->mt_directory, mt->mt_mountpoint)) {
      char buf[MAXPATHLEN+1];	/* must be same size as 'path' */
      xstrlcpy(buf, mt->mt_directory, sizeof(buf));
      xstrlcat(buf, &path[len], sizeof(buf));
      xstrlcpy(path, buf, l);
      *flag = 1;
    }
    show_pwd(mt->mt_next, path, l, flag);
    mt = mt->mt_child;
  }
}