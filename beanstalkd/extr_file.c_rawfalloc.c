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
 int errno ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

int
rawfalloc(int fd, int len)
{
    // We do not use ftruncate() because it might extend the file
    // with a sequence of null bytes or a hole.
    // posix_fallocate() is not portable enough, might fail for NFS.
    static char buf[4096] = {0};
    int i, w;

    for (i = 0; i < len; i += w) {
        w = write(fd, buf, sizeof buf);
        if (w == -1)
            return errno;
    }
    lseek(fd, 0, 0);            // do not care if this fails
    return 0;
}