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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ vc_hostfs_lseek64 (int,int /*<<< orphan*/ ,int) ; 

long vc_hostfs_lseek(int fildes, long offset, int whence)
{
   return (long) vc_hostfs_lseek64( fildes, (int64_t) offset, whence);
}