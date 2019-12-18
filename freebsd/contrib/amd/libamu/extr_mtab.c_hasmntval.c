#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mntent_t ;

/* Variables and functions */
 int hasmntvalerr (int /*<<< orphan*/ *,char*,int*) ; 

int
hasmntval(mntent_t *mnt, char *opt)
{
  int err, val = 0;

  err = hasmntvalerr(mnt, opt, &val);
  if (err)	   /* if there was an error (hasmntvalerr returned 1) */
    return 0;	   /* redundant: val==0 above, but leave here for clarity */
  /* otherwise there was no error */
  return val;
}