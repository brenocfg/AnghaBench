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
typedef  int /*<<< orphan*/  am_nfs_fh ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 

__attribute__((used)) static int
eq_fh(const am_nfs_fh *fh1, const am_nfs_fh *fh2)
{
  return (!memcmp((char *) fh1, (char *) fh2, sizeof(am_nfs_fh)));
}