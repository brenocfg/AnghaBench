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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MINOR (char*,int,void const*,unsigned int,int) ; 
 scalar_t__ write (int,void const*,unsigned int) ; 

int vc_hostfs_write(int fildes, const void *buf, unsigned int nbyte)
{
   int ret = (int) write(fildes, buf, nbyte);
   DEBUG_MINOR("vc_hostfs_write(%d,%p,%u) = %d", fildes, buf, nbyte, ret);
   return ret;
}