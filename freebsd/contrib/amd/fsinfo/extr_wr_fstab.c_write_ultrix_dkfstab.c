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
struct TYPE_3__ {char* d_dev; char* d_mountpt; char* d_fstype; char* d_opts; int d_freq; int d_passno; } ;
typedef  TYPE_1__ disk_fs ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,int,int) ; 

__attribute__((used)) static void
write_ultrix_dkfstab(FILE *ef, disk_fs *dp)
{
  fprintf(ef, "%s:%s:%s:%s:%d:%d\n",
	  dp->d_dev,
	  dp->d_mountpt,
	  dp->d_fstype,
	  dp->d_opts,
	  dp->d_freq,
	  dp->d_passno);
}