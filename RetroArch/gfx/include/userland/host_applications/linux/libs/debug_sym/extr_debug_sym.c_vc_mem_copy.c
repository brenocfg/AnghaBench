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
typedef  void* uint32_t ;
struct fb_dmacopy {void* length; void* src; void* dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,char const*,int,...) ; 
 int /*<<< orphan*/  FBIODMACOPY ; 
 int O_RDWR ; 
 int O_SYNC ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct fb_dmacopy*) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int vc_mem_copy(void *dst, uint32_t src, uint32_t length)
{
    const char *filename = "/dev/fb0";
    int memFd;
    struct fb_dmacopy ioparam;

    ioparam.dst = dst;
    ioparam.src = src;
    ioparam.length = length;

    if (( memFd = open( filename, O_RDWR | O_SYNC )) < 0 )
    {
        ERR( "Unable to open '%s': %s(%d)\n", filename, strerror( errno ), errno );
        return -errno;
    }

    if ( ioctl( memFd, FBIODMACOPY, &ioparam ) != 0 )
    {
        ERR( "Failed to get memory size via ioctl: %s(%d)\n",
            strerror( errno ), errno );
        close( memFd );
        return -errno;
    }
    close( memFd );
    return 0;
}